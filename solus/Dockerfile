FROM takano32/solus:4.4-budgie
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN eopkg dr Solus
RUN eopkg rr Solus
RUN eopkg ar Solus http://mirrors.rit.edu/solus/packages/shannon/eopkg-index.xml.xz
RUN eopkg rdb -y
RUN eopkg ur
RUN eopkg up -y

RUN eopkg install -y perl
RUN usysconf run -f ssl-certs

RUN eopkg install -y git
ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

# RUN eopkg install -y linux-headers linux-lts-headers linux-current-headers
RUN eopkg install -y llvm llvm-clang lldb
RUN eopkg install -yc system.devel
RUN eopkg install -y make
RUN eopkg install -y rpm

RUN eopkg install -y libelf-devel

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

