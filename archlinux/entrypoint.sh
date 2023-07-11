#!/bin/bash
set -eux

BUILD_DIR=/build-kernel/build
SUDO="sudo -u takano32"

mkdir -p $BUILD_DIR
chown -R takano32:takano32 $BUILD_DIR
cd $BUILD_DIR
$SUDO asp update linux
$SUDO asp export linux

cd $BUILD_DIR/linux
$SUDO updpkgsums && yes | $SUDO makepkg -seo
$SUDO git config --global http.version HTTP/1.1
$SUDO git config --global http.postBuffer 524288000
while :; do $SUDO makepkg -o --skippgpcheck && break || sleep 5; done

# `makepkg` in `$BUILD_DIR/linux`
JOBS=$(getconf _NPROCESSORS_ONLN)
JOBS=$(expr "$JOBS" + "$JOBS")
MAKEFLAGS="-j$(JOBS)"
$SUDO bash -c "MAKEFLAGS=$MAKEFLAGS makepkg --skippgpcheck"

cd $BUILD_DIR
mv linux/src/archlinux-linux/Documentation/output ../htmldocs
mkdir /build-kernel/zst-pkg
mv linux/*.zst ../zst-pkg
cd ..

if ! "$CI"; then
  python3 -m http.server
fi

