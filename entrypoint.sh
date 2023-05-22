#!/bin/bash
set -eux

LINUX_VERSION=v6.3

OS_ID=`grep ^ID= /etc/os-release | cut -d'=' -f2`
OS_ID=`echo echo $OS_ID | /bin/sh`
# NO_MAKE_PKG=("arch" "chimera")
MAKE_BINDEB_PKG=("ubuntu" "debian")
MAKE_BINRPM_PKG=("almalinux" "amzn" "centos" "gentoo" "opensuse-tumbleweed" "rocky")

MAKE_OPTS=""
if [ "$OS_ID" = "chimera" ]; then
  MAKE_OPTS="LLVM=1"
fi

PYTHON3_PIP_OPTS=""
if [ "$OS_ID" = "gentoo" ]; then
  PYTHON3_PIP_OPTS="--break-system-packages"
fi

cd /build-kernel/linux

git fetch --all --tags
git branch -D tag/$LINUX_VERSION || :
git checkout -b tag/$LINUX_VERSION refs/tags/$LINUX_VERSION || :
git checkout tag/$LINUX_VERSION

if [ -n "${CI:-}" ]; then
  rm -rf .git
fi

make $MAKE_OPTS clean

GENERIC_CONFIG_URL=https://kernel.ubuntu.com/~kernel-ppa/config/lunar/linux/6.2.0-21.21/amd64-config.flavour.generic
curl -L $GENERIC_CONFIG_URL > /build-kernel/build/.config
./scripts/config --file /build-kernel/build/.config \
	--disable DEBUG_INFO \
	--disable SYSTEM_TRUSTED_KEYS \
	--disable SYSTEM_REVOCATION_KEYS

make $MAKE_OPTS olddefconfig O=/build-kernel/build/

if [ "$OS_ID" != "ubuntu" ]; then
  # python3 -m pip install $PYTHON3_PIP_OPTS -r ./Documentation/sphinx/requirements.txt
  # python3 -m pip install $PYTHON3_PIP_OPTS docutils==0.17
  python3 -m pip install $PYTHON3_PIP_OPTS -U Sphinx
fi
JOBS=1
time make $MAKE_OPTS -j $JOBS htmldocs BUILDDIR=/build-kernel/htmldocs

LOCALVERSION=-`date +%Y%m%d`
JOBS=`getconf _NPROCESSORS_ONLN`
time make $MAKE_OPTS -j $JOBS            O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
time make $MAKE_OPTS -j $JOBS modules    O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
IFS="|"
if [[ "(${MAKE_BINDEB_PKG[*]})" =~ ${OS_ID} ]]; then
  time make $MAKE_OPTS -j $JOBS bindeb-pkg O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
fi
if [[ "(${MAKE_BINRPM_PKG[*]})" =~ ${OS_ID} ]]; then
  time make $MAKE_OPTS -j $JOBS binrpm-pkg O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
fi
unset IFS


cd /build-kernel
mkdir -p deb-pkg
mkdir -p rpm-pkg

# bindeb-pkg
mv *.deb *.buildinfo *.changes ./deb-pkg || :
# binrpm-pkg
## openSUSE
cp /usr/src/packages/RPMS/x86_64/*.rpm ./rpm-pkg || :
mv /usr/src/packages . || :
## RHEL Like
cp /root/rpmbuild/RPMS/x86_64/*.rpm ./rpm-pkg || :
mv /root/rpmbuild . || :

if [ -z "${CI:-}" ]; then
  python3 -m http.server
fi

