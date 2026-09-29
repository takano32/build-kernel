FROM mcr.microsoft.com/azurelinux/base/core:3.0
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN tdnf upgrade -y
RUN tdnf install -y git ca-certificates

# Azure Linux is CBL-Mariner renamed; its 3.0 kernel is the rolling-lts/mariner-3
# series of this tree, which entrypoint.sh picks the newest tag of.
ENV ORIGIN=https://github.com/microsoft/CBL-Mariner-Linux-Kernel.git

RUN tdnf install -y make gcc glibc-devel kernel-headers binutils bc bison flex \
    gawk perl python3 openssl-devel elfutils-libelf-devel
RUN tdnf install -y diffutils findutils tar xz cpio zstd kmod rsync rpm-build
RUN tdnf clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
