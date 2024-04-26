FROM ubuntu:24.04
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes

RUN cd /etc/apt/sources.list.d && sed 's/^Types: deb/Types: deb-src/g' < ubuntu.sources > deb-src.sources

RUN apt-get update
RUN apt-get install -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN apt-get build-dep -y linux
RUN apt-get install -y llvm clang lld
RUN apt-get install -y rpm
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

