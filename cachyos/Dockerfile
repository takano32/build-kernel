FROM cachyos/cachyos:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN pacman -Syyu --noconfirm
RUN pacman -S --noconfirm --needed git base-devel sudo

# makepkg refuses to run as root; -s installs the PKGBUILD's makedepends
# (clang, llvm, lld, rust, pahole, ...) through sudo.
RUN useradd -m takano32
RUN mkdir /build-kernel && chown takano32:takano32 /build-kernel
RUN echo "takano32 ALL=(ALL:ALL) NOPASSWD: ALL" > /etc/sudoers.d/takano32

# shared with archlinux/ and manjarolinux/; this branch clones CachyOS's own
# PKGBUILD instead of the distro's, and builds it with clang and ThinLTO.
ENV ARCH_SOURCE=cachyos

COPY ./entrypoint-arch.sh /entrypoint.sh
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
