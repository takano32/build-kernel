FROM takano32/solus:4.4-budgie
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN eopkg dr Solus
RUN eopkg rr Solus
RUN eopkg ar Solus https://mirrors.rit.edu/solus/packages/shannon/eopkg-index.xml.xz
RUN eopkg rdb -y
RUN eopkg ur
RUN eopkg up
RUN eopkg install -y git

ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --depth 1 ${ORIGIN} /build-kernel/linux
RUN while :; do cd /build-kernel/linux && git fetch --unshallow && break || sleep 5; done
RUN cd /build-kernel/linux && git pull --all

RUN eopkg install -y llvm clang lld
RUN eopkg install -y rpm

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

