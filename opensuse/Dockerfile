FROM opensuse/tumbleweed
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN zypper ref && zypper update -y
RUN zypper in -y which
RUN zypper in -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

# https://boxofcables.dev/building-a-kernel-for-wsl-on-opensuse/
RUN zypper in -y -t pattern devel_basis
RUN zypper rm -y busybox-diffutils
RUN zypper in -y bc openssl openssl-devel dwarves rpm-build libelf-devel
RUN zypper in -y zstd rpm-build rsync hostname

RUN zypper in -y python3 python3-pip graphviz
RUN zypper clean -a

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

