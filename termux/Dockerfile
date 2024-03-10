FROM termux/termux-docker
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

#COPY ./termux/resolv.conf /etc/resolv.conf
#RUN cat /etc/resolv.conf
RUN ping -c 3 8.8.8.8
RUN ping -c 3 google.com

RUN pkg update && pkg upgrade -y
RUN apt update && apt install -yq clang
RUN pkg install -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
#RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
#RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
#RUN cd /build-kernel/linux && git pull --all

RUN apt-get build-dep -y linux
RUN apt-get install -y llvm clang lld
RUN apt-get install -y rpm
RUN apt-get install -y curl python3-pip
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

