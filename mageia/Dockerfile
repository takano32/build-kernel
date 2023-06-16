FROM mageia:cauldron
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN echo "%_netsharedpath /sys:/proc" >> /etc/rpm/macros.dist
RUN dnf distro-sync -y --allowerasing
RUN dnf upgrade -y && dnf distro-sync -y && dnf clean all
RUN dnf install -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build

RUN urpmi --auto ncurses-devel make gcc bc bison flex openssl-devel
# RUN urpmi --auto elfutils-libelf-devel
RUN urpmi --auto lib64elfutils-devel elfutils
RUN urpmi --auto make diffutils cpio zstd rpm-build rsync
RUN urpmi --auto llvm clang lld

# make htmldocs
RUN urpmi --auto python3-pip graphviz texlive-latex librsvg2-tools

RUN yum -y clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

