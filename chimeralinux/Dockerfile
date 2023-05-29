FROM takano32/chimeralinux
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN apk update
RUN apk add bash git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build

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

RUN rm -rf /var/cache/apk/*

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

