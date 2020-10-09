FROM ubuntu:20.04
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS yes

RUN grep '^deb ' /etc/apt/sources.list | sed 's/^deb/deb-src/g' > /etc/apt/sources.list.d/deb-src.list

RUN apt-get update
RUN apt-get install -y git ccache fakeroot libncurses5-dev
RUN apt-get build-dep -y linux

RUN git clone --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git /build-kernel/linux
RUN mkdir /build-kernel/build

COPY ./docker-entrypoint.sh /
ENTRYPOINT ["/docker-entrypoint.sh"]
