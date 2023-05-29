FROM mageia:8
# FROM mageia:cauldron
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN dnf update -y
RUN dnf distro-sync -y
RUN dnf install -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build

RUN dnf distro-sync -y dnf python3-dnf dnf-conf && dnf clean all
RUN dnf distro-sync -y && dnf clean all

RUN urpmi --auto ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel
RUN urpmi --auto make diffutils cpio zstd rpm-build rsync

# make htmldocs
RUN urpmi --auto python3-pip graphviz texlive-latex librsvg2-tools

RUN yum -y clean all  && rm -rf /var/cache

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

