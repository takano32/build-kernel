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
  # debian and gentoo are not rpm distros, but both images install rpm.
  debian)                             PKG_DEB=true;  PKG_RPM=true  ;;
  gentoo)                                            PKG_RPM=true  ;;
  kali)                               PKG_DEB=true                 ;;
  almalinux|amzn|centos|fedora|rocky)                PKG_RPM=true  ;;
  opensuse-tumbleweed)                               PKG_RPM=true  ;;
  # linuxmint makes an rpm and no deb: bindeb-pkg was turned off for it and for
  # ubuntu in 2023-06 (47b8226), ubuntu's binrpm-pkg in 2023-07 (7f340db).
  # Neither commit says why, so re-enabling them is a follow-up to verify in CI.
  linuxmint)                                         PKG_RPM=true  ;;
  # chimera: the image has clang/lld but no gcc; apk-based, so neither deb nor rpm applies.
  chimera)                            USE_LLVM=true                ;;
  # build only: ubuntu, parrot, mageia, ol, solus, voidlinux, mariner, unknown
  *)                                                               ;;
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
  # rpm packaging needs these two, and not every yum-based Dockerfile has them.
  if command -v yum > /dev/null; then yum install -y dwarves perl; fi
  time "$MAKE" "${MAKE_OPTS[@]}" -j "$JOBS" binrpm-pkg O="$OUT" LOCALVERSION="$LOCALVERSION"
fi

# bindeb-pkg writes into the parent of O=; binrpm-pkg into /root/rpmbuild on
# RHEL-likes, Fedora, Debian and Gentoo and /usr/src/packages on openSUSE. Only
# the binary rpms are taken, not the SRPMS beside them.
shopt -s nullglob
for pkg in /build-kernel/*.deb /build-kernel/*.buildinfo /build-kernel/*.changes; do
  mv "$pkg" "$ARTIFACTS/"
done
for pkg in /root/rpmbuild/RPMS/*/*.rpm /usr/src/packages/RPMS/*/*.rpm; do
  cp "$pkg" "$ARTIFACTS/"
done
ls -l "$ARTIFACTS"  # so the CI log says what the build actually produced

# `docker compose up` leaves the container running: serve artifacts/ and build/
# on port 8000 so the results can be pulled from the host.
if ! "$CI"; then
  cd /build-kernel
  python3 -m http.server
fi
