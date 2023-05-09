FROM almalinux:9.1
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN yum -y install git

#ENV ORIGIN=https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
ENV ORIGIN=https://github.com/torvalds/linux.git
RUN git clone --jobs 32 ${ORIGIN} /build-kernel/linux
RUN mkdir /build-kernel/build
RUN mkdir /build-kernel/deb-pkg

#RUN apt-get build-dep -y linux
RUN yum -y clean all  && rm -rf /var/cache

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

