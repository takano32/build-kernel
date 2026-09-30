# BASE: debian-sid in docker-compose.yml builds the same with sid.
ARG BASE=debian:trixie-slim
FROM ${BASE}
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes
# The image lists its suites in deb822 form without deb-src, which build-dep
# needs. Adding the type in place works for trixie and sid alike (sid has no
# -security or -updates suites to list).
RUN sed -i 's/^Types: deb$/Types: deb deb-src/' /etc/apt/sources.list.d/debian.sources \
    && grep -q '^Types: deb deb-src$' /etc/apt/sources.list.d/debian.sources
RUN apt-get update
RUN apt-get install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN apt-get build-dep -y linux
RUN apt-get install -y llvm clang lld
RUN apt-get install -y zstd
RUN apt-get install -y rpm
RUN apt-get install -y curl python3-pip
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

