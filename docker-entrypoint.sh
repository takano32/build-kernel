#!/bin/bash
set -eux

cd /build-kernel/linux

GENERIC_CONFIG_URL=http://kernel.ubuntu.com/~kernel-ppa/config/bionic/linux/4.15.0-21.22/amd64-config.flavour.generic
curl -L $GENERIC_CONFIG_URL > /build-kernel/build/.config

./scripts/config --file /build-kernel/build/.config --disable DEBUG_INFO

make O=/build-kernel/build/ olddefconfig

time make -j9         O=/build-kernel/build/ LOCALVERSION=-stock

time make modules -j9 O=/build-kernel/build/ LOCALVERSION=-stock

time make bindeb-pkg  O=/build-kernel/build/ LOCALVERSION=-stock

cd /build-kernel
cp *.deb dpkg
python3 -m http.server
