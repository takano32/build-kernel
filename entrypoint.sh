#!/bin/bash
set -eux

cd /build-kernel/linux

git fetch --all
git checkout -b tag/v6.4-rc1 refs/tags/v6.4-rc1
if [ -n $CI ]; then
  rm -rf .git
fi

make clean

GENERIC_CONFIG_URL=https://kernel.ubuntu.com/~kernel-ppa/config/lunar/linux/6.2.0-21.21/amd64-config.flavour.generic
curl -L $GENERIC_CONFIG_URL > /build-kernel/build/.config
./scripts/config --file /build-kernel/build/.config \
	--disable DEBUG_INFO \
	--disable SYSTEM_TRUSTED_KEYS \
	--disable SYSTEM_REVOCATION_KEYS

make olddefconfig O=/build-kernel/build/

JOBS=`getconf _NPROCESSORS_ONLN`
JOBS=`expr $JOBS + $JOBS`
JOBS=`expr $JOBS + $JOBS`
LOCALVERSION=-`date +%Y%m%d`
time make -j $JOBS            O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
time make -j $JOBS modules    O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
time make -j $JOBS bindeb-pkg O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
time make -j $JOBS htmldocs BUILDDIR=/build-kernel/htmldocs

cd /build-kernel
mv *.deb *.buildinfo *.changes ./deb-pkg

if [ -z $CI ]; then
  python3 -m http.server
fi

