FROM debian:bookworm-slim
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes
COPY ./debian/sources.list /etc/apt/
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

