FROM openkylin/openkylin:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes

# openKylin ships a classic sources.list (huanghe). Same trick as Devuan: add
# the deb-src duplicates so apt-get build-dep and bindeb-pkg have sources.
RUN awk '{ print } /^deb /{ sub(/^deb /, "deb-src "); print }' /etc/apt/sources.list > /tmp/s \
    && mv /tmp/s /etc/apt/sources.list && grep -c '^deb-src ' /etc/apt/sources.list

RUN apt-get update
RUN apt-get install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

# Explicit list rather than build-dep: the archive is a snapshot and the
# source indexes are not guaranteed to line up with the binary ones.
RUN apt-get install -y build-essential dpkg-dev debhelper bc bison flex \
      libelf-dev libssl-dev libncurses-dev cpio zstd rsync
RUN apt-get install -y llvm clang lld
RUN apt-get install -y rpm python3-pip
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
