FROM gentoo/portage:latest as portage

FROM gentoo/stage3:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"
COPY --from=portage /var/db/repos/gentoo /var/db/repos/gentoo

RUN eselect news read new
RUN emerge -qv dev-vcs/git

RUN mkdir /build-kernel
RUN mkdir /build-kernel/build

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN emerge -qv sys-kernel/gentoo-sources

RUN emerge -qv dev-python/pip
RUN emerge -qv app-portage/flaggie
RUN flaggie media-libs/gd +fontconfig +truetype
RUN FEATURES="ipc-sandbox network-sandbox pid-sandbox" emerge -qv media-gfx/graphviz

RUN emerge -qv app-arch/rpm
RUN emerge -qv app-arch/dpkg
RUN touch /var/lib/dpkg/status

RUN emerge -qv app-portage/gentoolkit
RUN eclean --deep distfiles

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

