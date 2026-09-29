FROM opensuse/leap:16.0
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN zypper ref && zypper update -y
RUN zypper in -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

# Same toolchain as opensuse/ (Tumbleweed), from the release that SLES 16 shares.
RUN zypper rm -y busybox-gawk || :
RUN zypper in -y gawk
RUN zypper in -y -t pattern devel_basis
RUN zypper in -y diffutils bc openssl openssl-devel libelf-devel
RUN zypper in -y zstd rpm-build rsync hostname python3
RUN zypper clean -a

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
