FROM takano32/chimeralinux
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN apk update
RUN apk upgrade || apk fix
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
RUN apk add gm4 flex bison
RUN apk add elftoolchain-devel
RUN apk add openssl-devel
RUN apk add linux-headers

RUN useradd takano32
RUN mkdir -p /home/takano32
RUN chown -R takano32:takano32 /home/takano32
RUN echo "permit nopass root as takano32" > /etc/doas.conf
RUN chown root:root /etc/doas.conf
RUN chmod 0400 /etc/doas.conf
ENV SUDO="doas -u takano32"

RUN apk add opendoas
RUN mkdir archives
RUN chown takano32:takano32 archives
RUN curl https://ftp.gnu.org/gnu/coreutils/coreutils-9.3.tar.gz > coreutils-9.3.tar.gz
RUN chown takano32:takano32 coreutils-9.3.tar.gz
RUN mv coreutils-9.3.tar.gz archives
RUN cd archives && $SUDO tar xvf coreutils-9.3.tar.gz
RUN cd archives/coreutils-9.3 && $SUDO ./configure && $SUDO make && make install

RUN apk add llvm
RUN rm -rf /var/cache/apk/*

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

