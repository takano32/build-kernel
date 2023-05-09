FROM ubuntu:23.04
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes

RUN grep '^deb ' /etc/apt/sources.list | sed 's/^deb/deb-src/g' > /etc/apt/sources.list.d/deb-src.list

RUN apt-get update
RUN apt-get install -y git

#ENV ORIGIN=https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --jobs 32 ${ORIGIN} /build-kernel/linux
RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/deb-pkg

RUN apt-get build-dep -y linux

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

