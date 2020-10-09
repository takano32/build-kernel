#!/bin/bash
set -eux

cd /build-kernel/linux

# cp /boot/config-`uname -r` /build-kernel/build/.config
curl -L http://kernel.ubuntu.com/~kernel-ppa/config/bionic/linux/4.15.0-21.22/amd64-config.flavour.generic > /build-kernel/build/.config

./scripts/config --file /build-kernel/build/.config --disable DEBUG_INFO

make O=/build-kernel/build/ olddefconfig

time make -j9         O=/build-kernel/build/ LOCALVERSION=-stock

time make modules -j9 O=/build-kernel/build/ LOCALVERSION=-stock

time make bindeb-pkg  O=/build-kernel/build/ LOCALVERSION=-stock

sleep 1d
