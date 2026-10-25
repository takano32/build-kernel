# SUSE Linux Enterprise's toolchain, from the public BCI image (no
# subscription needed for bci-base, unlike the full SLES repos).
FROM registry.suse.com/bci/bci-base:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN zypper ref && zypper in -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN zypper in -y -t pattern devel_basis
RUN zypper in -y gcc make bc bison flex libelf-devel openssl-devel \
      ncurses-devel diffutils cpio zstd rpm-build rsync hostname
RUN zypper in -y dwarves libdw-devel
RUN zypper in -y python3 python3-pip graphviz
RUN zypper clean -a

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
