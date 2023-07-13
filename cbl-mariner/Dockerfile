FROM mcr.microsoft.com/cbl-mariner/base/core:2.0
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN yum upgrade -y
RUN yum install -y git

ENV ORIGIN=https://github.com/microsoft/CBL-Mariner-Linux-Kernel.git
RUN git config --global http.sslVerify false
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN yum install -y make gcc bc bison flex openssl-devel
RUN yum install -y binutils diffutils cpio zstd rpm-build rsync
RUN yum install -y llvm clang lld
RUN yum install -y glibc-headers

RUN yum clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

