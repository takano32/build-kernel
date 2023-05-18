FROM takano32/chimeralinux
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN apk update
RUN apk add bash git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git config --global http.version HTTP/1.1
RUN git config --global http.postBuffer 524288000
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN cd /build-kernel/linux && git fetch --unshallow
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/rpm-pkg

RUN apk add gmake curl
RUN ln -s /usr/sbin/gmake /usr/local/bin/make
#RUN yum install -y ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel
#RUN yum install -y make diffutils cpio zstd rpm-build rsync

# make htmldocs
RUN apk add python-pip
RUN apk add graphviz
#RUN yum install -y python3-pip graphviz texlive-latex librsvg2-tools

RUN apk add clang
RUN apk add flex bison
RUN apk add elftoolchain-devel
RUN apk add openssl-devel
RUN apk add linux-headers

#RUN yum -y clean all  && rm -rf /var/cache

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

