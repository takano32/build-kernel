FROM mageia:cauldron
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"


RUN echo "%_db_backend sqlite" >> /etc/rpm/macros.db
RUN rm -rf /var/lib/rpm
RUN rpmdb --rebuilddb --define "_db_backend sqlite"
RUN echo "%_netsharedpath /sys:/proc" >> /etc/rpm/macros.dist
RUN dnf upgrade -y --releasever=8
RUN dnf distro-sync -y --releasever=9
RUN dnf upgrade -y --best --releasever=9 dnf python3-dnf dnf-conf
RUN dnf install -y --best --releasever=9 yum
RUN dnf clean packages
RUN yum install -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN yum install -y python3-dnf
RUN yum install -y ncurses-devel make gcc bc bison flex openssl-devel
RUN yum install -y lib64elfutils-devel elfutils
RUN yum install -y make diffutils cpio zstd rpm-build rsync
RUN yum install -y llvm clang lld

# make htmldocs
RUN yum install -y python3-pip graphviz texlive librsvg2

RUN dnf clean all
RUN yum clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

