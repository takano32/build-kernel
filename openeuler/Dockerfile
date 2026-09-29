FROM openeuler/openeuler:24.03-lts-sp4
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN dnf upgrade -y
RUN dnf install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN dnf install -y make gcc glibc-devel kernel-headers binutils bc bison flex \
    gawk perl python3 openssl-devel elfutils-libelf-devel
RUN dnf install -y diffutils findutils tar xz cpio zstd kmod rsync rpm-build
RUN dnf clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
