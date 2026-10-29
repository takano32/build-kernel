# Pin the release: the trees and mageia:latest move around (latest was 8 when
# this file was written, and it is 10 now).
FROM mageia:10
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"


RUN echo "%_db_backend sqlite" >> /etc/rpm/macros.db
RUN rm -rf /var/lib/rpm
RUN rpmdb --rebuilddb --define "_db_backend sqlite"
RUN echo "%_netsharedpath /sys:/proc" >> /etc/rpm/macros.dist
# www.mageia.org hosts the mirrorlist and went offline for security
# maintenance on 2026-10-22, so every dnf call died on a 404 from it and took
# this job with it; the Mageia 8 trees are gone from the mirrors too. The image
# already ships the same repos as static baseurls (mirrors.kernel.org) on
# commented-out lines, so switch to those and stop depending on that host.
RUN sed -i -e 's|^mirrorlist=|#mirrorlist=|' -e 's|^#baseurl=|baseurl=|' /etc/yum.repos.d/*.repo
RUN dnf distro-sync -y --releasever=10
RUN dnf upgrade -y --best --releasever=10
RUN dnf install -y --best --releasever=10 yum
RUN dnf clean packages
RUN yum clean all
RUN yum install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

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

