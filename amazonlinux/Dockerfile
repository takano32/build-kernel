FROM amazonlinux:2023
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN yum -y install git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN yum install -y ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel
RUN yum install -y make diffutils cpio zstd rpm-build rsync hostname elfutils-devel
RUN yum install -y dwarves perl

# make htmldocs
RUN yum install -y python3-pip graphviz texlive-latex librsvg2-tools

RUN yum install -y openssl
RUN yum -y clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

