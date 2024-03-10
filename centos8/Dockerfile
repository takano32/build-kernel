FROM centos:8.4.2105
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV CENTOS=mirror.centos.org
ENV VAULT=vault.centos.org
RUN cd /etc/yum.repos.d && sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-*
RUN cd /etc/yum.repos.d && sed -i "s|#baseurl=http://$CENTOS|baseurl=http://$VAULT|g" /etc/yum.repos.d/CentOS-*


RUN yum -y install git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN yum install -y ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel
RUN yum install -y make diffutils cpio zstd rpm-build rsync

# make htmldocs
RUN yum install -y python3-pip graphviz texlive-latex librsvg2-tools

RUN yum -y clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

