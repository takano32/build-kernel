FROM ghcr.io/void-linux/void-linux:latest-thin-bb-x86_64
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN xbps-install -Suvy xbps
# The ghcr base image lags the repository. Without a full upgrade, packages
# installed below link against newer libraries than the image ships (rsync
# needed libacl ACL_1.3), so bring the whole system up to date first.
RUN xbps-install -Suvy
RUN xbps-install -Suvy bash
RUN xbps-install -Suvy git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN xbps-install -Suvy make gcc bc bison flex elfutils elfutils-devel libelf openssl-devel
RUN xbps-install -Suvy rpm
#RUN yum install -y make diffutils cpio zstd rpm-build rsync

# make htmldocs
RUN xbps-install -Suvy python3-pip graphviz texlive librsvg

RUN xbps-install -Suvy curl
RUN xbps-install -Suvy coreutils findutils diffutils
RUN xbps-install -Suvy llvm clang lld
RUN xbps-install -Suvy rpm

RUN xbps-install -Suvy tar xz
# headers_install, which binrpm-pkg runs, needs rsync
RUN xbps-install -Suvy rsync
RUN xbps-remove -Oo

RUN echo "ID=voidlinux" > /etc/os-release
COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

