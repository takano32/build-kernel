FROM alt:p11
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

RUN apt-get update && apt-get dist-upgrade -y
RUN apt-get install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN apt-get install -y make gcc bc bison flex gawk perl python3 \
    libssl-devel libelf-devel
RUN apt-get install -y diffutils findutils tar xz cpio zstd kmod rsync
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
