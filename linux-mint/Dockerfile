# Linux Mint's own image; it already lists the deb-src entries build-dep needs.
FROM linuxmintd/mint22.3-amd64
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes


RUN apt-get update
RUN apt-get upgrade -y && apt-get dist-upgrade -y
RUN apt-get install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN apt-get build-dep -y linux
RUN apt-get install -y rpm
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

