#!/bin/bash
# Entrypoint for the Arch family. archlinux and manjarolinux build their
# distro's own `linux` PKGBUILD straight out of the distro repositories;
# cachyos builds CachyOS's linux-cachyos PKGBUILD instead. The three used to be
# near-identical copies of this script -- they differ only in where the PKGBUILD
# comes from and how makepkg is called -- so they now share one file and pick a
# branch with ARCH_SOURCE.
#
# -x stays on because a CI log is the only debugger these builds get.
set -eux

CI=${CI:-false}
BUILD_DIR=/build-kernel/build
ARTIFACTS=/build-kernel/artifacts
SUDO="sudo -u takano32"
# ARCH_SOURCE:
#   pkgctl  (default) `pkgctl repo clone linux` -- the distro's own PKGBUILD,
#                     built with the toolchain that package ships with.
#   cachyos           CachyOS's linux-cachyos PKGBUILD, which compiles with
#                     clang and ThinLTO and so cannot share a gcc ccache.
ARCH_SOURCE=${ARCH_SOURCE:-pkgctl}

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR" "$ARTIFACTS"
chown -R takano32:takano32 "$BUILD_DIR"
cd "$BUILD_DIR"

case "$ARCH_SOURCE" in
    pkgctl)
        $SUDO pkgctl repo clone --protocol=https linux

        cd "$BUILD_DIR/linux"
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

        # mv linux/src/archlinux-linux/Documentation/output ../htmldocs
        mv "$BUILD_DIR"/linux/*.zst "$ARTIFACTS/"
        ;;
    cachyos)
        # The PKGBUILD takes any non-empty $CI as its own CI: a size-optimized
        # build without DEBUG_KERNEL and without bpftool's vmlinux.h. Keep that
        # for CI, but do not let CI=false turn it on for a local run.
        if ! "$CI"; then unset CI; fi

        $SUDO git clone --depth 1 https://github.com/CachyOS/linux-cachyos.git

        cd "$BUILD_DIR/linux-cachyos/linux-cachyos"
        # _processor_opt=generic: the default is -march=native of whatever runner
        # the job lands on; generic keeps the package usable on any x86-64.
        # --skippgpcheck: the tarball's .asc needs the CachyOS maintainers' keys,
        # which this container does not have; b2sums still verify the source.
        $SUDO env ${CI+CI="$CI"} _processor_opt=generic \
            makepkg -s --noconfirm --skippgpcheck

        mv ./*.pkg.tar.zst "$ARTIFACTS/"
        ls -l "$ARTIFACTS"
        ;;
    *)
        echo "ARCH_SOURCE=$ARCH_SOURCE is not one of: pkgctl, cachyos" >&2
        exit 1
        ;;
esac

cd /build-kernel
if [ -z "${CI+x}" ] || ! "$CI"; then
    if command -v python3 > /dev/null; then
        exec python3 -m http.server
    fi
    exec python -m http.server
fi
