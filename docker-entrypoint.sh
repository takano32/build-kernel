#!/bin/bash
set -eux

cd /build-kernel/linux

git fetch origin
git checkout -b tag/v5.17 refs/tags/v5.17

# GENERIC_CONFIG_URL=https://kernel.ubuntu.com/~kernel-ppa/config/jammy/linux/5.15.0-16.16/amd64-config.flavour.generic
GENERIC_CONFIG_URL=https://kernel.ubuntu.com/~kernel-ppa/config/focal/linux/5.4.0-49.53/amd64-config.flavour.generic
curl -L $GENERIC_CONFIG_URL > /build-kernel/build/.config

./scripts/config --file /build-kernel/build/.config --disable DEBUG_INFO

make O=/build-kernel/build/ olddefconfig

time make -j16            O=/build-kernel/build/ LOCALVERSION=-stock

time make -j16 modules    O=/build-kernel/build/ LOCALVERSION=-stock

time make -j16 bindeb-pkg O=/build-kernel/build/ LOCALVERSION=-stock

cd /build-kernel
cp *.deb dpkg


python3 -m http.server
