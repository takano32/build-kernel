#!/bin/bash
set -eux

CI=${CI:-false}
LINUX_VERSION=v6.3

OS_ID=`grep ^ID= /etc/os-release | cut -d'=' -f2`
OS_ID=`echo echo $OS_ID | /bin/sh`

# NO_MAKE_PKG=("arch" "chimera")
MAKE_BINDEB_PKG=("ubuntu" "debian")
MAKE_BINRPM_PKG=("ubuntu" "debian" "gentoo"
  "almalinux" "amzn" "centos" "opensuse-tumbleweed" "rocky")
MAKE_HTMLDOCS=()

USE_LLVM=("chimera")
MAKE_OPTS=""
IFS="|"
if [[ "(${USE_LLVM[*]})" =~ ${OS_ID} ]]; then
  MAKE_OPTS="LLVM=1 $MAKE_OPTS"
fi
unset IFS

if "$CI"; then
  MAKE_OPTS="V=0 $MAKE_OPTS"
fi

USE_PIP_WITH_BREAK_SYSTEM_PACKAGES=("debian" "gentoo")
PYTHON3_PIP_OPTS=""
IFS="|"
if [[ "(${USE_PIP_WITH_BREAK_SYSTEM_PACKAGES[*]})" =~ ${OS_ID} ]]; then
  PYTHON3_PIP_OPTS="--break-system-packages"
fi
unset IFS
cd /build-kernel/linux

git fetch --all --tags
git branch -D tag/$LINUX_VERSION || :
git checkout -b tag/$LINUX_VERSION refs/tags/$LINUX_VERSION || :
git checkout tag/$LINUX_VERSION

if "$CI"; then
  rm -rf .git
fi

make $MAKE_OPTS clean

GENERIC_CONFIG_URL=https://kernel.ubuntu.com/~kernel-ppa/config/mantic/linux/6.3.0-5.5/amd64-config.flavour.generic
curl -L $GENERIC_CONFIG_URL > /build-kernel/build/.config
./scripts/config --file /build-kernel/build/.config \
	--disable DEBUG_INFO \
	--disable SYSTEM_TRUSTED_KEYS \
	--disable SYSTEM_REVOCATION_KEYS

make $MAKE_OPTS olddefconfig O=/build-kernel/build/

IFS="|"
if [[ "(${MAKE_HTMLDOCS[*]})" =~ ${OS_ID} ]]; then
  if [ "$OS_ID" != "ubuntu" ]; then
    python3 -m pip install $PYTHON3_PIP_OPTS -U Sphinx
  fi
  time make $MAKE_OPTS htmldocs BUILDDIR=/build-kernel/htmldocs
fi
unset IFS

LOCALVERSION=-`date +%Y%m%d`
JOBS=`getconf _NPROCESSORS_ONLN`
time make $MAKE_OPTS -j $JOBS            O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
time make $MAKE_OPTS -j $JOBS modules    O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
IFS="|"
if [[ "(${MAKE_BINDEB_PKG[*]})" =~ ${OS_ID} ]]; then
  mkdir -p /build-kernel/deb-pkg
  time make $MAKE_OPTS -j $JOBS bindeb-pkg O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
fi
if [[ "(${MAKE_BINRPM_PKG[*]})" =~ ${OS_ID} ]]; then
  mkdir -p /build-kernel/rpm-pkg
  time make $MAKE_OPTS -j $JOBS binrpm-pkg O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
fi
unset IFS


cd /build-kernel

# bindeb-pkg
mv *.deb *.buildinfo *.changes ./deb-pkg || :
# binrpm-pkg
## openSUSE
cp /usr/src/packages/RPMS/x86_64/*.rpm ./rpm-pkg || :
mv /usr/src/packages . || :
## RHEL Like
cp /root/rpmbuild/RPMS/x86_64/*.rpm ./rpm-pkg || :
mv /root/rpmbuild . || :

if ! "$CI"; then
  python3 -m http.server
fi

