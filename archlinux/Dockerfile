FROM archlinux:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN pacman-db-upgrade
RUN pacman -Syyu --noconfirm

RUN pacman -Syy --noconfirm git
RUN pacman -Syy --noconfirm asp base-devel
RUN pacman -Syy --noconfirm pacman-contrib
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

