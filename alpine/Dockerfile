FROM alpine:3.24
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN apk upgrade --no-cache
RUN apk add --no-cache bash git

ENV ORIGIN=https://github.com/gregkh/linux.git

# musl + GCC: chimeralinux is the other musl image, but it builds with clang.
RUN apk add --no-cache build-base bc bison flex perl python3 \
    elfutils-dev openssl-dev linux-headers
# The busybox applets are not enough for kbuild's scripts: swap in the GNU
# tools, and musl-utils for the getconf that entrypoint.sh counts CPUs with.
RUN apk add --no-cache coreutils findutils diffutils grep sed gawk tar xz \
    zstd cpio kmod rsync musl-utils

# objtool sizes its signal stack with musl's fixed SIGSTKSZ, which is too small
# on AMX-capable runners; see alpine/signal.h. Kbuild reads HOSTCFLAGS from the
# environment and passes it on to objtool.
COPY ./alpine/signal.h /alpine-include/signal.h
ENV HOSTCFLAGS="-I/alpine-include"

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
