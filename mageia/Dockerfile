FROM mageia:cauldron
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN urpmi --auto --auto-update
RUN urpmi.addmedia --distrib --mirrorlist '$MIRRORLIST'
RUN urpmi.update -a && urpmi --auto-select

RUN urpmi --auto git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git config --global http.version HTTP/1.1
RUN git config --global http.postBuffer 524288000
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN cd /build-kernel/linux && git fetch --unshallow
RUN cd /build-kernel/linux && git pull --all

RUN mkdir /build-kernel/build

RUN urpmi --auto ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel
RUN urpmi --auto make diffutils cpio zstd rpm-build rsync

# make htmldocs
RUN urpmi --auto python3-pip graphviz texlive-latex librsvg2-tools

RUN yum -y clean all  && rm -rf /var/cache

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

