# CentOS Linux 8, the last CentOS release before Stream (EOL 2021-12). Docker
# Hub's newest centos image is 8.4.2105; the repositories now live on
# vault.centos.org, whose $releasever 8 tree is the final 8.5.2111, so the
# upgrade below brings the image up to that release.
FROM centos:8.4.2105
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV CENTOS=mirror.centos.org
ENV VAULT=vault.centos.org
RUN cd /etc/yum.repos.d && sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-*
RUN cd /etc/yum.repos.d && sed -i "s|#baseurl=http://$CENTOS|baseurl=http://$VAULT|g" /etc/yum.repos.d/CentOS-*
RUN yum -y upgrade && grep -q 8.5.2111 /etc/centos-release

RUN yum -y install git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN yum install -y ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel
RUN yum install -y make diffutils cpio zstd rpm-build rsync hostname elfutils-devel

# make htmldocs
RUN yum install -y python3-pip graphviz texlive-latex librsvg2-tools

RUN yum -y clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

