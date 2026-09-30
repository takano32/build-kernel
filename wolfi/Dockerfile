# Wolfi: apk packages on glibc, a combination no other image covers.
FROM chainguard/wolfi-base:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

# wolfi-base now lists Chainguard's own repository, which needs credentials;
# the public Wolfi OS repository is signed by the wolfi-signing key the image
# already carries.
RUN echo https://packages.wolfi.dev/os > /etc/apk/repositories
RUN apk update && apk upgrade
RUN apk add bash git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN apk add build-base bc bison flex perl python3 elfutils-dev openssl-dev \
    linux-headers
RUN apk add coreutils findutils diffutils grep sed gawk gnutar xz zstd cpio kmod \
    rsync posix-libc-utils

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
