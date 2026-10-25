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
# python (3.15) and python-pip, not python3/python3-pip.
RUN dnf install -y python python-pip graphviz
RUN dnf clean all

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
