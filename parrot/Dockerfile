FROM parrotsec/core
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes

# deb.parrot.sh is a CDN, and one of its nodes (23.19.10.58 as of 2026-09) answers
# 404 for files it should have, which failed about every other CI run. mirrors.mit.edu
# was the replacement until 2026-10-25, when it started answering 404 for tzdata
# 2026e while its dists/echo/Release looked current. dotsrc has both (checked:
# dists/echo/Release dated today, and the tzdata pool file answers 200), so use it
# and fail here if the URL ever changes again.
RUN find /etc/apt -type f \( -name '*.list' -o -name '*.sources' \) \
      -exec sed -i 's|https\?://deb.parrot.sh/parrot|https://mirrors.dotsrc.org/parrot|g' {} + \
    && grep -rq mirrors.dotsrc.org /etc/apt

RUN if ls /etc/apt/sources.list.d/*.sources > /dev/null 2>&1; then \
      sed 's/^Types: deb/Types: deb-src/g' /etc/apt/sources.list.d/*.sources > /etc/apt/sources.list.d/deb-src.sources; \
    else \
      cat /etc/apt/sources.list /etc/apt/sources.list.d/*.list 2>/dev/null | grep '^deb ' | sed 's/^deb/deb-src/g' > /etc/apt/sources.list.d/deb-src.list; \
    fi

RUN apt-get update
RUN apt-get install -y git

ENV ORIGIN=https://github.com/gregkh/linux.git

RUN apt-get upgrade -y && apt-get dist-upgrade -y
RUN apt-get build-dep -y linux
RUN apt-get install -y llvm clang lld
RUN apt-get install -y rpm
RUN apt-get install -y curl python3-pip
RUN apt-get clean

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]

