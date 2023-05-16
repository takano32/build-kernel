FROM rockylinux:9.1
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN yum -y install git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git config --global http.version HTTP/1.1
RUN git config --global http.postBuffer 524288000
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN cd /build-kernel/linux && git fetch --unshallow
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/rpm-pkg

RUN yum install -y ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel
RUN yum install -y make diffutils cpio zstd rpm-build rsync

# make htmldocs
RUN yum install -y python3-pip graphviz texlive-latex librsvg2-tools
RUN yum install -y texlive

RUN yum -y clean all  && rm -rf /var/cache

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

