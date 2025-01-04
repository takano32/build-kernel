#!/bin/bash
set -eux

CI=${CI:-false}
LINUX_VERSION=v6.12

MAKE=gmake
if which gmake > /dev/null; then
  MAKE="gmake"
else
  MAKE="make"
fi
OS_ID=`grep ^ID= /etc/os-release | cut -d'=' -f2`
OS_ID=`echo echo $OS_ID | /bin/sh`

# NO_MAKE_PKG=("chimera")
MAKE_BINDEB_PKG=("debian" "kali")
MAKE_BINRPM_PKG=("debian" "gentoo"
  "almalinux" "amzn" "centos" "fedora" "linuxmint"
  "opensuse-tumbleweed" "rocky")
  # mageia, ol voidlinux
MAKE_HTMLDOCS=("ol")

# USE_LLVM=("chimera" "debian" "kali" "voidlinux")
USE_LLVM=("chimera")
MAKE_OPTS=""

IFS="|"
if [[ "(${USE_LLVM[*]})" =~ ${OS_ID} ]]; then
  MAKE_OPTS="LLVM=1 $MAKE_OPTS"
fi
unset IFS

if "$CI"; then
  MAKE_OPTS="V=0 $MAKE_OPTS"
else
  MAKE_OPTS="V=12 $MAKE_OPTS"
fi

USE_PIP_WITH_BREAK_SYSTEM_PACKAGES=("gentoo")
PYTHON3_PIP_OPTS=""
IFS="|"
if [[ "(${USE_PIP_WITH_BREAK_SYSTEM_PACKAGES[*]})" =~ ${OS_ID} ]]; then
  PYTHON3_PIP_OPTS="--break-system-packages"
fi
unset IFS
cd /build-kernel/linux

git fetch --all --tags
if [ "mariner" = "$OS_ID" ]; then
  git branch -D rolling-lts/mariner || :
  git checkout -b rolling-lts/mariner -t origin/rolling-lts/mariner || :
else
  git branch -D tag/$LINUX_VERSION || :
  git checkout -b tag/$LINUX_VERSION refs/tags/$LINUX_VERSION || :
fi

if "$CI"; then
  rm -rf .git
fi

$MAKE $MAKE_OPTS clean
mkdir -p /build-kernel/build
#GENERIC_CONFIG_URL=https://kernel.ubuntu.com/~kernel-ppa/config/mantic/linux/6.3.0-5.5/amd64-config.flavour.generic
#curl -kL $GENERIC_CONFIG_URL > /build-kernel/build/.config
./scripts/config --file /build-kernel/build/.config \
  --enable MODULES \
  --disable ANDROID_BINDER_IPC \
  --disable ANDROID_BINDERFS \
  --disable SYSTEM_TRUSTED_KEYS \
  --disable SYSTEM_REVOCATION_KEYS \
  --disable DEBUG_INFO

$MAKE $MAKE_OPTS olddefconfig O=/build-kernel/build/

IFS="|"
if [[ "(${MAKE_HTMLDOCS[*]})" =~ ${OS_ID} ]]; then
  if [[ "$OS_ID" =~ ubuntu\|debian\|linuxmint ]]; then
    python3 -m pip install $PYTHON3_PIP_OPTS -U Sphinx
  fi
  if ! "$CI"; then
    time $MAKE $MAKE_OPTS htmldocs BUILDDIR=/build-kernel/htmldocs
  fi
fi
unset IFS

LOCALVERSION=-$(date +%Y%m%d)
JOBS=$(getconf _NPROCESSORS_ONLN)
JOBS=$(expr "$JOBS" + "$JOBS")
JOBS=$(expr "$JOBS" + "$JOBS")
time $MAKE $MAKE_OPTS -j $JOBS            O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
time $MAKE $MAKE_OPTS -j $JOBS modules    O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
IFS="|"
if [[ "(${MAKE_BINDEB_PKG[*]})" =~ ${OS_ID} ]]; then
  mkdir -p /build-kernel/deb-pkg
  time $MAKE $MAKE_OPTS -j $JOBS bindeb-pkg O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
fi
if [[ "(${MAKE_BINRPM_PKG[*]})" =~ ${OS_ID} ]]; then
  [ -x "$(which yum)" ] && yum install -y dwarves perl
  mkdir -p /build-kernel/rpm-pkg
  time $MAKE $MAKE_OPTS -j $JOBS binrpm-pkg O=/build-kernel/build/ LOCALVERSION=$LOCALVERSION
fi
unset IFS


cd /build-kernel

# bindeb-pkg
mv ./*.deb ./*.buildinfo ./*.changes ./deb-pkg || :
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

