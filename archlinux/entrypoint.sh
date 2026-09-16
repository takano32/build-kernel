#!/bin/bash
set -eux

CI=${CI:-false}
BUILD_DIR=/build-kernel/build
SUDO="sudo -u takano32"

rm -rf $BUILD_DIR/* || :
mkdir -p $BUILD_DIR
chown -R takano32:takano32 $BUILD_DIR
# The ccache dir is bind-mounted from the CI workspace (build.yml) and arrives
# owned by the runner user; makepkg runs as takano32, so hand it over. Stats are
# zeroed so the numbers printed after the build describe this run only.
mkdir -p /build-kernel/ccache
chown -R takano32:takano32 /build-kernel/ccache
$SUDO ccache --zero-stats
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
JOBS=$(expr "$JOBS" + "$JOBS")
echo "MAKEFLAGS=\"-j$JOBS\"" | tee -a /etc/makepkg.conf
$SUDO makepkg --skippgpcheck
$SUDO ccache --show-stats

cd $BUILD_DIR
# mv linux/src/archlinux-linux/Documentation/output ../htmldocs
mkdir -p /build-kernel/artifacts
mv linux/*.zst /build-kernel/artifacts/
cd ..

if ! "$CI"; then
  python3 -m http.server
fi

