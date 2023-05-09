FROM almalinux:9.1
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN yum -y install git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --jobs 32 ${ORIGIN} /build-kernel/linux
RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/rpm-pkg

#RUN yum install -y ncurses-devel
#RUN yum install -y hmaccalc zlib-devel binutils-devel elfutils-libelf-devel
RUN yum install -y ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel
RUN yum install -y make
# make htmldocs
RUN yum install -y python3-pip
RUN yum install -y graphviz texlive-latex librsvg2-tools

RUN yum -y clean all  && rm -rf /var/cache

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

