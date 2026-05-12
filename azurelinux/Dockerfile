FROM mcr.microsoft.com/azurelinux/base/core:3.0

LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN tdnf upgrade -y
RUN tdnf install -y ca-certificates git
RUN tdnf clean all

ENV ORIGIN=https://github.com/microsoft/CBL-Mariner-Linux-Kernel.git

RUN git config --global http.sslVerify false
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN tdnf install -y \
    make gcc bc bison flex gawk \
    openssl-devel \
    binutils diffutils cpio zstd rpm-build rsync \
    llvm clang lld \
    glibc-devel kernel-headers \
    elfutils-libelf-devel dwarves perl \
    tar gzip xz

RUN tdnf clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh

EXPOSE 8000

ENTRYPOINT ["/entrypoint.sh"]
