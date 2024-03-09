#!/bin/bash
set -eux

CI=${CI:-false}
BUILD_DIR=/build-kernel/build
SUDO="sudo -u takano32"

rm -rf $BUILD_DIR/* || :
mkdir -p $BUILD_DIR
chown -R takano32:takano32 $BUILD_DIR
cd $BUILD_DIR
$SUDO pkgctl repo clone --protocol=https linux

cd $BUILD_DIR/linux
$SUDO updpkgsums && yes | $SUDO makepkg -seo
$SUDO git config --global http.version HTTP/1.1
$SUDO git config --global http.postBuffer 524288000
while :; do $SUDO makepkg -o --skippgpcheck && break || sleep 5; done

# `makepkg` in `$BUILD_DIR/linux`
JOBS=$(getconf _NPROCESSORS_ONLN)
JOBS=$(expr "$JOBS" + "$JOBS")
$SUDO MAKEFLAGS="-j$JOBS" makepkg --skippgpcheck

cd $BUILD_DIR
mv linux/src/archlinux-linux/Documentation/output ../htmldocs
mkdir /build-kernel/zst-pkg
mv linux/*.zst ../zst-pkg
cd ..

if ! "$CI"; then
  python3 -m http.server
fi

