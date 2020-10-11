FROM ubuntu:20.04
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS yes

RUN grep '^deb ' /etc/apt/sources.list | sed 's/^deb/deb-src/g' > /etc/apt/sources.list.d/deb-src.list

RUN apt-get update
RUN apt-get install -y git

RUN git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git /build-kernel/linux
RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/dpkg

RUN apt-get install -y ccache fakeroot libncurses5-dev
RUN apt-get build-dep -y linux

# make htmldocs
RUN apt-get install -y graphviz imagemagick dvipng
RUN apt-get install -y python3-venv fonts-noto-cjk latexmk librsvg2-bin
RUN ln -s /usr/bin/python3.8 /usr/local/bin/python

COPY ./docker-entrypoint.sh /
EXPOSE 8000
ENTRYPOINT ["/docker-entrypoint.sh"]
