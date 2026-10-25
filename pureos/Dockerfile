FROM pureos/pureos:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes

# PureOS writes a classic sources.list, like Devuan. Duplicate each `deb` line
# as `deb-src`: build-dep and bindeb-pkg both want the source indexes.
RUN awk '{ print } /^deb /{ sub(/^deb /, "deb-src "); print }' /etc/apt/sources.list > /tmp/s \
    && mv /tmp/s /etc/apt/sources.list && grep -c '^deb-src ' /etc/apt/sources.list

RUN apt-get update
RUN apt-get install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

# PureOS is Debian with its own archive, so the kernel's build-deps are the
# Debian ones; fall back to the explicit list when the archive has no source
# index for the installed version.
RUN apt-get build-dep -y linux || apt-get install -y build-essential dpkg-dev debhelper
RUN apt-get install -y bc bison flex libelf-dev libssl-dev libncurses-dev cpio zstd rsync
RUN apt-get install -y llvm clang lld
RUN apt-get install -y rpm curl python3-pip
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
