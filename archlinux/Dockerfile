FROM archlinux:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN pacman-db-upgrade
RUN pacman -Syyu --noconfirm

RUN pacman -Syy --noconfirm git
RUN pacman -Syy --noconfirm devtools base-devel
RUN pacman -Syy --noconfirm pacman-contrib
# ccache: the kernel compile is ~140 of the job's ~150 minutes; a warm cache
# (kept by actions/cache in build.yml, mounted at /build-kernel/ccache) removes
# most of it. hash_dir=false because the source dir name changes with every
# minor kernel version and would otherwise miss the whole cache; the only
# effect is DW_AT_comp_dir inside the debug info.
RUN pacman -Syy --noconfirm ccache
RUN sed -i '/^BUILDENV=/s/!ccache/ccache/' /etc/makepkg.conf \
    && grep -qE '^BUILDENV=.*[( ]ccache[ )]' /etc/makepkg.conf
RUN printf 'cache_dir = /build-kernel/ccache\nmax_size = 4G\nhash_dir = false\n' > /etc/ccache.conf
RUN pacman -Scc

RUN useradd takano32
RUN mkdir /build-kernel
RUN mkdir /home/takano32
RUN chown -R takano32.takano32 /build-kernel /home/takano32
RUN echo "takano32 ALL=(ALL:ALL) NOPASSWD: ALL" > /etc/sudoers.d/takano32
ENV SUDO="sudo -u takano32"

COPY ./archlinux/entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

