FROM openmandriva/cooker:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN dnf install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

# Cooker already builds with clang by default in its own packaging, but the
# kernel's Makefile takes gcc: keep both, no LLVM=1 unless asked for.
# OpenMandriva spells the library packages out: lib64elfutils-devel,
# lib64openssl-devel and lib64ncurses-devel (there is no openssl-devel).
RUN dnf install -y make gcc bc bison flex lib64elfutils-devel lib64openssl-devel \
      lib64ncurses-devel diffutils cpio zstd rpm-build rsync
RUN dnf install -y llvm clang lld

# /usr/bin/ld is a symlink to ld.lld here, and the kernel's x86 boot link
# rejects lld: "ld: error: undefined symbol: ZO_kernel_info" out of
# arch/x86/boot/setup.elf. The compile itself is gcc, so point LD at the GNU
# linker that binutils ships alongside it.
ENV LD=ld.bfd
# python (3.15) and python-pip, not python3/python3-pip.
RUN dnf install -y python python-pip graphviz
RUN dnf clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
