#!/bin/bash
# Build CachyOS's own kernel from its PKGBUILD, the way archlinux/ and
# manjarolinux/ build Arch's. linux-cachyos compiles with clang and ThinLTO,
# so it cannot share their gcc ccache and runs without one.
set -euxo pipefail

CI=${CI:-false}
BUILD_DIR=/build-kernel/build
ARTIFACTS=/build-kernel/artifacts
SUDO="sudo -u takano32"

# The PKGBUILD takes any non-empty $CI as its own CI: a size-optimized build
# without DEBUG_KERNEL and without bpftool's vmlinux.h. Keep that for CI, but
# do not let CI=false turn it on for a local run.
if ! "$CI"; then unset CI; fi

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR" "$ARTIFACTS"
chown takano32:takano32 "$BUILD_DIR"
cd "$BUILD_DIR"
$SUDO git clone --depth 1 https://github.com/CachyOS/linux-cachyos.git
cd linux-cachyos/linux-cachyos

# _processor_opt=generic: the default is -march=native of whatever runner the
# job lands on; generic keeps the package usable on any x86-64.
# --skippgpcheck: the tarball's .asc needs the CachyOS maintainers' keys,
# which this container does not have; b2sums still verify the source.
$SUDO env ${CI+CI="$CI"} _processor_opt=generic \
  makepkg -s --noconfirm --skippgpcheck

mv ./*.pkg.tar.zst "$ARTIFACTS/"
ls -l "$ARTIFACTS"

if [ -z "${CI+x}" ]; then
  cd /build-kernel
  python -m http.server
fi
