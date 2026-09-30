# BASE: gentoo-musl in docker-compose.yml builds the same on the musl stage3.
ARG BASE=gentoo/stage3:latest
FROM gentoo/portage:latest as portage

FROM ${BASE}
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"
COPY --from=portage /var/db/repos/gentoo /var/db/repos/gentoo

RUN eselect news read new
# Python 3.14 only. The tree's targets are python3_14, but a stage3 can
# still carry python packages built for an older one alone (the musl stage3:
# python3_13), and anything that then wants them for 3.14 (Sphinx, for
# linux-docs) slot-conflicts with the installed copies gemato needs.
# Rebuild just those for the tree's targets; without --deep this stays at
# the stage3's python packages (26 on the musl stage3) instead of an
# @world update that rebuilt gcc and took gentoo from ~40 to ~150 minutes.
RUN emerge -q1uN $(qlist -IC dev-python/ app-portage/gemato)
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

