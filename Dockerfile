FROM ubuntu:23.04
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes

RUN grep '^deb ' /etc/apt/sources.list | sed 's/^deb/deb-src/g' > /etc/apt/sources.list.d/deb-src.list

RUN apt-get update
RUN apt-get install -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git config --global http.version HTTP/1.1
RUN git config --global http.postBuffer 524288000
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN cd /build-kernel/linux && git fetch --unshallow
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/deb-pkg

RUN apt-get build-dep -y linux
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

