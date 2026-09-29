FROM photon:5.0
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN tdnf upgrade -y
RUN tdnf install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN tdnf install -y make gcc glibc-devel linux-api-headers binutils bc bison \
    flex gawk perl python3 openssl-devel elfutils-libelf-devel
RUN tdnf install -y diffutils findutils tar xz cpio zstd kmod rsync rpm-build
RUN tdnf clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
