FROM mageia:cauldron
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN echo "%_netsharedpath /sys:/proc" >> /etc/rpm/macros.dist
RUN dnf distro-sync -y --allowerasing
RUN dnf upgrade -y && dnf distro-sync -y && dnf clean all
RUN dnf makecache
RUN dnf install -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build

RUN dnf install -y ncurses-devel make gcc bc bison flex openssl-devel
RUN dnf install -y elfutils-libelf-devel
RUN dnf install -y lib64elfutils-devel elfutils
RUN dnf install -y make diffutils cpio zstd rpm-build rsync
RUN dnf install -y llvm clang lld

# make htmldocs
RUN dnf install -y python3-pip graphviz texlive-latex librsvg2-tools

RUN dnf clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

