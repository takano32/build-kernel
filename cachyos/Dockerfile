FROM cachyos/cachyos:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN pacman -Syyu --noconfirm
RUN pacman -S --noconfirm --needed git

ENV ORIGIN=https://github.com/gregkh/linux.git

# Unlike archlinux/ and manjarolinux/, this builds the pinned tag through
# entrypoint.sh rather than the distro's own kernel: linux-cachyos is built
# with clang and ThinLTO, so it could not share their gcc ccache, and a full
# config without one takes hours. What this checks is CachyOS's toolchain.
RUN pacman -S --noconfirm --needed base-devel bc cpio perl python libelf \
    openssl zstd xz tar rsync kmod
RUN pacman -Scc --noconfirm

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
