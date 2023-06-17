#!/bin/bash
set -eux

SUDO="sudo -u takano32"

$SUDO mkdir -p /build-kernel/build/linux
$SUDO rm -rf   /build-kernel/build/linux
$SUDO mkdir -p /build-kernel/build/linux
cd /build-kernel/build/linux
$SUDO asp update linux
$SUDO asp export linux
$SUDO cp -a linux/* .
$SUDO rm -rf linux

# `makepkg` in `/build-kernel/bulid/linux`
$SUDO makepkg --skippgpcheck

cd /build-kernel/build
mv linux/src/archlinux-linux/Documentation/output ../htmldocs
mv linux/*.zst ../zst-pkg
cd ..

if ! "$CI"; then
  python3 -m http.server
fi


