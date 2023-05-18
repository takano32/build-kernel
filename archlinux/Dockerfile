FROM archlinux:latest
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV BUILD_DIR=/build-kernel/build

RUN mkdir /build-kernel
RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/zst-pkg

RUN yes | pacman -Sy git

RUN yes | pacman -S asp base-devel
RUN yes | pacman -S pacman-contrib

RUN pacman -Scc

RUN useradd takano32
RUN mkdir /home/takano32
RUN chown -R takano32.takano32 /build-kernel /home/takano32
RUN echo "takano32 ALL=(ALL:ALL) NOPASSWD: ALL" > /etc/sudoers.d/takano32
ENV SUDO="sudo -u takano32"
RUN $SUDO git config --global http.version HTTP/1.1
RUN $SUDO git config --global http.postBuffer 524288000

RUN cd $BUILD_DIR && $SUDO asp update linux
RUN cd $BUILD_DIR && $SUDO asp export linux
RUN cd $BUILD_DIR/linux && $SUDO updpkgsums
RUN cd $BUILD_DIR/linux && yes | $SUDO makepkg -seo
RUN cd $BUILD_DIR/linux && $SUDO makepkg -o --skippgpcheck

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

