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
# effect is DW_AT_comp_dir inside the debug info. A full build's objects need
# a bit over 5 GB at the default compression; 4G thrashed (255 cleanups per
# run, 81% hits). 5G stays inside GitHub's 10 GB cache quota for the two
# Arch-based jobs (an entry is about 0.9x of ccache's own size figure), and
# zstd level 6 shrinks what has to fit.
RUN pacman -Syy --noconfirm ccache
RUN sed -i '/^BUILDENV=/s/!ccache/ccache/' /etc/makepkg.conf \
    && grep -qE '^BUILDENV=.*[( ]ccache[ )]' /etc/makepkg.conf
RUN printf 'cache_dir = /build-kernel/ccache\nmax_size = 5G\ncompression_level = 6\nhash_dir = false\n' > /etc/ccache.conf
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

