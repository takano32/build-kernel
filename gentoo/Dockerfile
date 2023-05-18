FROM gentoo/portage:latest as portage

FROM gentoo/stage3:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"
COPY --from=portage /var/db/repos/gentoo /var/db/repos/gentoo

RUN mkdir /build-kernel
RUN emerge -qv dev-vcs/git

ENV ORIGIN https://github.com/torvalds/linux.git
RUN git config --global http.version HTTP/1.1
RUN git config --global http.postBuffer 524288000
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN cd /build-kernel/linux && git fetch --unshallow
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/rpm-pkg
RUN mkdir /build-kernel/deb-pkg

RUN emerge -qv sys-kernel/gentoo-sources

RUN emerge -qv dev-python/pip
RUN emerge -qv app-portage/flaggie
RUN flaggie media-libs/gd +fontconfig +truetype
RUN emerge -qv media-gfx/graphviz

RUN emerge -qv app-arch/rpm
RUN emerge -qv app-arch/dpkg
RUN touch /var/lib/dpkg/status

RUN emerge -qv app-portage/gentoolkit
RUN eclean --deep distfiles

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
