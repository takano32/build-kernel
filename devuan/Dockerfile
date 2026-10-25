FROM devuan/devuan:daedalus
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes

# Devuan still writes a classic sources.list, and build-dep / bindeb-pkg want
# the source indexes too. Duplicate every `deb` line as a `deb-src` one.
RUN awk '{ print } /^deb /{ sub(/^deb /, "deb-src "); print }' /etc/apt/sources.list > /tmp/s \
    && mv /tmp/s /etc/apt/sources.list && grep -c '^deb-src ' /etc/apt/sources.list

RUN apt-get update
RUN apt-get install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

# build-dep instead of a hand-written list: on Devuan the kernel package's
# dependencies are the same as Debian's, and the list changes with the kernel.
RUN apt-get build-dep -y linux || apt-get install -y build-essential dpkg-dev debhelper
RUN apt-get install -y bc bison flex libelf-dev libssl-dev libncurses-dev cpio zstd rsync
RUN apt-get install -y llvm clang lld
RUN apt-get install -y rpm curl python3-pip
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
