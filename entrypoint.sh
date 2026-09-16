#!/bin/bash
# Build one pinned stable kernel tag on whatever distro this container is,
# run bindeb-pkg/binrpm-pkg on the distros the table below enables it for, and
# leave the results in /build-kernel/artifacts. archlinux/ and manjarolinux/ do
# not use this script: they build Arch's official PKGBUILD from their own entrypoint.
# -x stays on because a CI log is the only debugger these builds get.
set -euxo pipefail

CI=${CI:-false}
# The 7.1 series went EOL on 2026-09-02, so the pin moved on to 7.2.x.
LINUX_VERSION=${LINUX_VERSION:-v7.2.6}
# Every Dockerfile sets ENV ORIGIN; cbl-mariner's points at Microsoft's tree.
ORIGIN=${ORIGIN:-https://github.com/gregkh/linux.git}
SRC=/build-kernel/linux
OUT=/build-kernel/build
ARTIFACTS=/build-kernel/artifacts
# mkspec and mkdebian write "$user@$host" into the package metadata and shell
# out to `hostname` for the host part unless these are set; the oraclelinux and
# cbl-mariner images have no hostname binary. Fixed values also keep the
# packager field and /proc/version the same from one run to the next.
export KBUILD_BUILD_USER=build-kernel
export KBUILD_BUILD_HOST=docker

MAKE="make"
if command -v gmake > /dev/null; then MAKE="gmake"; fi

# Values in /etc/os-release may be quoted; sourcing unquotes them for us.
# shellcheck source=/dev/null
. /etc/os-release

# Per-distro knobs, matched exactly on $ID. The arrays this replaces were tested
# with [[ "(${LIST[*]})" =~ $OS_ID ]], which asks whether the ID is a substring
# of the list -- backwards, so an ID like "ol" matched a list containing "solus".
PKG_DEB=false
PKG_RPM=false
USE_LLVM=false
case "$ID" in
  # Debian family: `apt-get build-dep linux` brings dpkg-dev and debhelper, and
  # every one of these images also installs rpm, so both targets apply. ubuntu
  # and linuxmint had bindeb-pkg turned off in 2023-06 (47b8226) and ubuntu's
  # binrpm-pkg in 2023-07 (7f340db) without a recorded reason; back on since 2026-09.
  debian|ubuntu|linuxmint|kali|parrot)          PKG_DEB=true; PKG_RPM=true ;;
  # rpm-native distros. ol, mageia and voidlinux were dropped in 2024-03 (155cde8),
  # most likely over rpmbuild's BuildRequires check (that commit also added a
  # run-time `yum install dwarves perl` for the RHEL-likes); mariner and solus
  # were never tried. The check is skipped now (see binrpm-pkg below).
  almalinux|amzn|centos|fedora|rocky|ol|mageia) PKG_RPM=true ;;
  opensuse-tumbleweed|mariner|voidlinux|solus)  PKG_RPM=true ;;
  # gentoo installs rpm and dpkg, but bindeb-pkg needs debhelper, which Gentoo does not package.
  gentoo)                                       PKG_RPM=true ;;
  # chimera: the image has clang/lld but no gcc; apk-based, so neither deb nor rpm applies.
  chimera)                                      USE_LLVM=true ;;
  # build only: anything else, e.g. rhel (the UBI image is defined but not in CI).
  *) ;;
esac

if "$CI"; then
  MAKE_OPTS=(V=0)   # CI logs are long enough without per-file command lines
else
  MAKE_OPTS=(V=12)
fi
if "$USE_LLVM"; then MAKE_OPTS+=(LLVM=1); fi

# A tag that cannot be fetched has to fail the build: the old script checked out
# with `|| :`, which silently built whatever HEAD the image happened to carry
# and let CI go green on a kernel nobody asked for.
fetch_tag() {
  local tag=$1
  local attempt
  for attempt in 1 2 3; do
    [ "$attempt" -eq 1 ] || sleep 5  # GitHub drops a fetch every so often
    if [ -d "$SRC/.git" ]; then
      # A local re-run: `docker compose up` re-uses the container, tree and all.
      if git -C "$SRC" fetch --depth 1 origin "refs/tags/$tag:refs/tags/$tag" &&
        git -C "$SRC" checkout --detach "refs/tags/$tag"; then
        return 0
      fi
    elif git clone --depth 1 --branch "$tag" "$ORIGIN" "$SRC"; then
      return 0
    fi
  done
  echo "cannot fetch $tag from $ORIGIN" >&2
  exit 1
}

# The pinned version does not exist in Microsoft's tree, so CBL-Mariner is built
# at the newest tag of its rolling LTS series instead.
if [ "$ID" = "mariner" ]; then
  LINUX_VERSION=$(git ls-remote --tags --refs "$ORIGIN" 'refs/tags/rolling-lts/mariner-3/*' |
    sed 's|.*refs/tags/||' | sort -V | tail -n 1)
  if [ -z "$LINUX_VERSION" ]; then
    echo "no rolling-lts/mariner-3/* tag in $ORIGIN" >&2
    exit 1
  fi
fi
fetch_tag "$LINUX_VERSION"

# The container is discarded anyway, and even a shallow clone's .git is a few
# hundred MB on the CI runner, where disk is the scarcest resource.
if "$CI"; then rm -rf "$SRC/.git"; fi
cd "$SRC"

"$MAKE" "${MAKE_OPTS[@]}" clean
mkdir -p "$OUT"
# There is no .config yet -- scripts/config creates one -- so olddefconfig gives
# every symbol its default: alldefconfig plus MODULES=y, a compile-test kernel
# and not a bootable distro kernel. The --disable lines are left over from when
# an Ubuntu generic config was the base (2023-2024) and are no-ops against
# defaults; they stay so that dropping a distro config back in keeps working.
./scripts/config --file "$OUT/.config" \
  --enable MODULES \
  --disable ANDROID_BINDER_IPC \
  --disable ANDROID_BINDERFS \
  --disable SYSTEM_TRUSTED_KEYS \
  --disable SYSTEM_REVOCATION_KEYS \
  --disable DEBUG_INFO
"$MAKE" "${MAKE_OPTS[@]}" olddefconfig O="$OUT"

# Save the config before compiling: a build that dies still leaves it for upload.
mkdir -p "$ARTIFACTS"
cp "$OUT/.config" "$ARTIFACTS/config"

LOCALVERSION=-$(date +%Y%m%d)
JOBS=$(getconf _NPROCESSORS_ONLN)
# clang needs far more memory per job; oversubscribing OOM-kills the CI runner
if ! "$USE_LLVM"; then JOBS=$((JOBS * 4)); fi
time "$MAKE" "${MAKE_OPTS[@]}" -j "$JOBS"            O="$OUT" LOCALVERSION="$LOCALVERSION"
time "$MAKE" "${MAKE_OPTS[@]}" -j "$JOBS" modules    O="$OUT" LOCALVERSION="$LOCALVERSION"
if "$PKG_DEB"; then
  time "$MAKE" "${MAKE_OPTS[@]}" -j "$JOBS" bindeb-pkg O="$OUT" LOCALVERSION="$LOCALVERSION"
fi
if "$PKG_RPM"; then
  # kernel.spec's BuildRequires (dwarves, perl, rsync, ...) describe a build from
  # source, but binrpm-pkg only packages the tree compiled above (rpmbuild
  # --build-in-place --noprep), so the check can fail only on missing metadata
  # packages. That is what kept ol, mageia, mariner, voidlinux and solus out and
  # forced a run-time `yum install dwarves perl` on the RHEL-likes; --nodeps skips it.
  time "$MAKE" "${MAKE_OPTS[@]}" -j "$JOBS" binrpm-pkg RPMOPTS=--nodeps O="$OUT" LOCALVERSION="$LOCALVERSION"
fi

# bindeb-pkg writes the packages into the parent of O=. binrpm-pkg defines
# _topdir as $OUT/rpmbuild (since v6.6), so the rpms are in there and not in
# ~/rpmbuild or /usr/src/packages as they once were: the old script copied from
# those two and had silently collected nothing since then.
shopt -s nullglob
for pkg in /build-kernel/*.deb /build-kernel/*.buildinfo /build-kernel/*.changes; do
  mv "$pkg" "$ARTIFACTS/"
done
for pkg in "$OUT"/rpmbuild/RPMS/*/*.rpm; do
  cp "$pkg" "$ARTIFACTS/"
done
ls -l "$ARTIFACTS"  # so the CI log says what the build actually produced

# `docker compose up` leaves the container running: serve artifacts/ and build/
# on port 8000 so the results can be pulled from the host.
if ! "$CI"; then
  cd /build-kernel
  python3 -m http.server
fi
