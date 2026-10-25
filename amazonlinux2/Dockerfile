# Amazon Linux 2, not a BASE arg on amazonlinux/Dockerfile: its package set is
# the 2018-era one (gcc 7.3, make 3.82, rpm 4.11) and the htmldocs packages the
# 2023 image installs do not exist here.
FROM amazonlinux:2
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN yum -y install git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN yum -y groupinstall "Development Tools"
RUN yum -y install ncurses-devel bc bison flex elfutils-libelf-devel openssl-devel \
      diffutils cpio zstd rpm-build rsync which
RUN yum -y install python3 python3-pip
RUN yum clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
