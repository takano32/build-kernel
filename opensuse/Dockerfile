FROM opensuse/tumbleweed
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN mkdir /build-kernel

RUN zypper ref && zypper update -y
RUN zypper in -y which
RUN zypper in -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git config --global http.version HTTP/1.1
RUN git config --global http.postBuffer 524288000
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN cd /build-kernel/linux && git fetch --unshallow
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/rpm-pkg

# https://boxofcables.dev/building-a-kernel-for-wsl-on-opensuse/
RUN zypper in -y -t pattern devel_basis
RUN zypper in -y bc openssl openssl-devel dwarves rpm-build libelf-devel
RUN zypper in -y zstd rpm-build rsync

RUN zypper in -y python3-pip graphviz
RUN zypper clean -a

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
