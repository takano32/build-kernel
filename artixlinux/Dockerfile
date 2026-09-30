# Artix Linux: Arch without systemd. It builds the pinned tag through
# entrypoint.sh like the non-Arch images; archlinux/ already covers Arch's
# PKGBUILD.
FROM artixlinux/artixlinux:base-devel
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN pacman -Syyu --noconfirm
RUN pacman -S --noconfirm --needed git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN pacman -S --noconfirm --needed base-devel bc cpio perl python libelf \
    openssl zstd xz tar rsync kmod
RUN pacman -Scc --noconfirm

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
