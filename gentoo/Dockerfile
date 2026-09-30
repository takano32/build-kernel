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

