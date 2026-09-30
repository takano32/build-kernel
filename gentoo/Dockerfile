# BASE: gentoo-musl, gentoo-llvm and gentoo-musl-llvm in docker-compose.yml
# build the same on the musl, LLVM and musl+LLVM stage3s.
ARG BASE=gentoo/stage3:latest
FROM gentoo/portage:latest as portage

FROM ${BASE}
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"
COPY --from=portage /var/db/repos/gentoo /var/db/repos/gentoo

RUN eselect news read new
# Python 3.14 only, on every stage3. The tree already targets python3_14,
# but a stage3 can carry packages built for an older target alone (the musl
# one: python3_13), and anything that then wants them for 3.14 (Sphinx, for
# linux-docs) slot-conflicts with the installed copies gemato needs. Pin the
# targets and rebuild just the packages installed for an older one, without
# --deep: 56 merges on the musl stage3, none on the others (emerge -p against
# the current tree), where an @world update pulled in gcc and 160-odd
# packages and took gentoo from ~40 to ~150 minutes.
RUN printf 'PYTHON_TARGETS="python3_14"\nPYTHON_SINGLE_TARGET="python3_14"\n' >> /etc/portage/make.conf
RUN P=$(grep -lE 'python_(single_)?targets?_python3_1[0-3]( |$)' /var/db/pkg/*/*/USE \
      | sed 's|/var/db/pkg/||; s|/USE||; s/-[0-9].*//' | sort -u); \
    if [ -n "$P" ]; then emerge -q1uN $P; fi
# The musl LLVM stage3 has no gcc, and dev-lang/rust-bin (pulled in by git's
# rust USE and by rpm's sequoia USE, through rpm-sequoia) wants
# llvm-runtimes/libgcc or sys-devel/gcc: the former is masked, so emerge
# built gcc 16 and binutils from source under clang, which kept
# gentoo-musl-llvm in its image build for well over 100 minutes. Leave Rust
# out there: git without its rust parts, rpm verifying signatures with
# libgcrypt instead of Sequoia.
RUN if [ -e /lib/ld-musl-x86_64.so.1 ] && [ "$(portageq envvar CC)" = clang ]; then \
      mkdir -p /etc/portage/package.use \
      && printf 'dev-vcs/git -rust\napp-arch/rpm -sequoia\n' > /etc/portage/package.use/no-rust; \
    fi
RUN emerge -qv dev-vcs/git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN emerge -qv sys-kernel/gentoo-sources
# Only linux-docs needs ~amd64; keywording it alone keeps its Sphinx
# dependencies on stable.
RUN echo "sys-kernel/linux-docs ~amd64" > /etc/portage/package.accept_keywords/linux-docs
RUN emerge -qv sys-kernel/linux-docs

# RUN emerge -qv dev-python/pip
# RUN emerge -qv app-portage/flaggie
# RUN flaggie media-libs/gd +fontconfig +truetype
# RUN FEATURES="ipc-sandbox network-sandbox pid-sandbox" emerge -qv media-gfx/graphviz

RUN emerge -qv app-arch/rpm
# musl has no obstack; dpkg's dependency sys-libs/obstack-standalone provides
# it, but the ebuild does not link it, so on musl dpkg failed with undefined
# references to _obstack_free. Link it for dpkg there only (glibc has none).
RUN if [ -e /lib/ld-musl-x86_64.so.1 ]; then \
      mkdir -p /etc/portage/env /etc/portage/package.env \
      && echo 'LIBS="-lobstack"' > /etc/portage/env/obstack.conf \
      && echo 'app-arch/dpkg obstack.conf' > /etc/portage/package.env/dpkg; \
    fi
RUN emerge -qv app-arch/dpkg
RUN touch /var/lib/dpkg/status

RUN emerge -qv app-portage/gentoolkit

# Only used by the musl build, through HOSTCFLAGS in docker-compose.yml.
COPY ./musl/signal.h /musl-include/signal.h
RUN eclean --deep distfiles

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

