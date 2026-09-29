FROM termux/termux-docker:x86_64
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

# Termux's package manager refuses to run as root, and $PREFIX belongs to the
# image's system user (1000), so the packages go in as that user.
USER 1000:1000
RUN apt update && apt upgrade -y -o Dpkg::Options::=--force-confnew
RUN apt install -y bash git

ENV ORIGIN=https://github.com/gregkh/linux.git

# There is no gcc in Termux, so this is an LLVM=1 build (see entrypoint.sh).
RUN apt install -y clang lld llvm make bison flex bc perl python \
    libelf openssl
RUN apt install -y coreutils findutils diffutils grep sed gawk tar xz-utils \
    zstd cpio rsync getconf
RUN apt clean

# The rootfs is Android's: no /bin, /usr/bin or /etc/os-release. Kbuild runs
# /bin/sh and its scripts' #!/usr/bin/env lines directly, and there is no
# termux-exec in a container to rewrite them, so point both at $PREFIX/bin;
# entrypoint.sh reads its distro knobs from /etc/os-release.
USER root
RUN [ -e /bin ] || ln -s "$PREFIX/bin" /bin
RUN mkdir -p /usr && { [ -e /usr/bin ] || ln -s "$PREFIX/bin" /usr/bin; }
RUN mkdir -p /etc && echo "ID=termux" > /etc/os-release
RUN mkdir -p /build-kernel

# Bionic is not glibc, and kbuild's host programs assume glibc headers. Kbuild
# reads HOSTCFLAGS from the environment and hands it to objtool and libsubcmd too.
# -I: termux/elf.h, a glibc-style <elf.h> on top of Bionic's; see there.
# -Wno-unused-function: Bionic's <sys/cdefs.h> defines __always_inline without
# `inline`, and tools/include/linux/compiler.h only defines its own #ifndef, so
# the static READ_ONCE helpers there become unused plain functions, which
# objtool's -Werror refuses.
COPY ./termux/elf.h /termux-include/elf.h
ENV HOSTCFLAGS="-I/termux-include -Wno-unused-function"

# The image's own /entrypoint.sh drops to the system user, who could not write
# to the artifacts directory CI bind-mounts; /entrypoint_root.sh keeps root.
COPY ./entrypoint.sh /build-kernel.sh
RUN chmod 755 /build-kernel.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint_root.sh", "bash", "/build-kernel.sh"]
