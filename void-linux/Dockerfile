FROM ghcr.io/void-linux/void-linux:latest-thin-bb-x86_64
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN xbps-install -Suvy bash

RUN xbps-install -Suvy git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build

RUN xbps-install -Suvy make gcc bc bison flex elfutils elfutils-devel libelf openssl-devel
RUN xbps-install -Suvy rpm
#RUN yum install -y make diffutils cpio zstd rpm-build rsync

# make htmldocs
RUN xbps-install -Suvy python3-pip graphviz texlive librsvg

RUN xbps-install -Suvy curl
RUN xbps-install -Suvy coreutils findutils diffutils
RUN xbps-install -Suvy llvm clang lld
RUN xbps-install -Suvy rpm

RUN xbps-install -Suvy tar xz
RUN xbps-remove -Oo

RUN echo "ID=voidlinux" > /etc/os-release
COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

