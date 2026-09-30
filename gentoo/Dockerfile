# BASE: gentoo-musl in docker-compose.yml builds the same on the musl stage3.
ARG BASE=gentoo/stage3:latest
FROM gentoo/portage:latest as portage

FROM ${BASE}
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"
COPY --from=portage /var/db/repos/gentoo /var/db/repos/gentoo

RUN eselect news read new
# Bring the stage3 up to the portage tree first. The musl stage3 lags it:
# its python packages were built for python3_13 only, and the ~amd64
# linux-docs below pulls in Sphinx for python3_14, which left requests,
# urllib3, certifi and friends in slot conflicts with the installed gemato.
RUN emerge -quDN @world
RUN emerge -qv dev-vcs/git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN emerge -qv sys-kernel/gentoo-sources
RUN ACCEPT_KEYWORDS="~amd64" emerge -qv sys-kernel/linux-docs

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

