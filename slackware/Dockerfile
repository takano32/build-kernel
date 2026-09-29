# There is no official image. aclemons/slackware is the maintained unofficial
# one; the -full tag is a complete install, which matters because slackpkg does
# not resolve dependencies. It already has everything the build needs.
FROM aclemons/slackware:15.0-full
LABEL maintainer "TAKANO Mitsuhiro <takano32@gmail.com>"

ENV ORIGIN=https://github.com/gregkh/linux.git

COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
EXPOSE 8000
ENTRYPOINT ["/entrypoint.sh"]
