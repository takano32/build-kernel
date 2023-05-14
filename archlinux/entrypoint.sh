#!/bin/bash
set -eux

SUDO="sudo -u takano32"

cd /build-kernel/build/linux

$SUDO asp update linux
$SUDO asp export linux
$SUDO cp -a linux/* .
$SUDO rm -rf linux

$SUDO makepkg --skippgpcheck

cd /build-kernel/build
mv linux/src/archlinux-linux/Documentation/output ../htmldocs
mv linux/*.zst ../zst-pkg
cd ..
python3 -m http.server

