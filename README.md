[![Build Linux Kernel](https://github.com/takano32/build-kernel/actions/workflows/build-all.yml/badge.svg)](https://github.com/takano32/build-kernel/actions/workflows/build-all.yml)
![Distributions](https://img.shields.io/badge/distributions-43-blue)

# build-kernel

Build Linux Kernel with Docker Compose.

```
$ docker compose up ubuntu
```

## What a build does

Each service is one distribution's image with that distribution's toolchain.
On start the container fetches a single pinned stable kernel tag
(`LINUX_VERSION` in `entrypoint.sh`; override with
`docker compose run -e LINUX_VERSION=v7.2.6 ubuntu`), builds it with an
`alldefconfig`-based config plus modules, runs `bindeb-pkg` / `binrpm-pkg`
where the image has the tools, and serves the results from
`/build-kernel/artifacts` on port 8000 (see the port mapping in
`docker-compose.yml`). A tag that cannot be fetched fails the build.

`archlinux` and `manjarolinux` build Arch's official `linux` PKGBUILD
instead, `cachyos` builds CachyOS's `linux-cachyos` PKGBUILD (clang and
ThinLTO, `_processor_opt=generic`), and `azurelinux` and `cbl-mariner`
build Microsoft's kernel tree at its newest `rolling-lts/mariner-3` tag.

## CI

Every push, plus a schedule on Monday and Thursday 00:00 UTC, builds all 43
distributions. Each job uploads `artifacts/` (the packages and the kernel
config) as a workflow artifact. The longest jobs are the three that
build their distro's full kernel config, archlinux, manjarolinux and
cachyos, at two to three hours each; they run in parallel with the rest,
so a whole run takes about as long as the slowest of them.

## Supported distributions

CI builds the kernel on these 43 distributions and variants:

almalinux, almalinux-kitten, alpine, alpine-edge, altlinux, amazonlinux,
anolisos, archlinux, artixlinux, azurelinux, cachyos, cbl-mariner,
centos, centos8, chimeralinux, debian, debian-sid, fedora,
fedora-rawhide, gentoo, gentoo-llvm, gentoo-musl, gentoo-musl-llvm,
kalilinux, linux-mint, mageia, manjarolinux, miraclelinux, opencloudos,
openeuler, opensuse, opensuse-leap, oraclelinux, parrot, photon,
rockylinux, slackware, solus, termux, ubuntu, void-linux,
void-linux-musl, wolfi

The `-rawhide`, `-sid`, `-edge` and `-kitten` jobs build on development
branches to catch toolchain changes before they reach a release;
`gentoo-musl` and `void-linux-musl` build those distributions on musl,
and `gentoo-llvm` and `gentoo-musl-llvm` on Gentoo's LLVM stage3s, where
the kernel is built with clang (LLVM=1).

`centos` is CentOS Stream 10; `centos8` is CentOS Linux 8.5.2111, the
last CentOS release before Stream, from vault.centos.org. Likewise
`azurelinux` is Azure Linux 3.0 and `cbl-mariner` stays on CBL-Mariner
2.0, its end-of-life predecessor.

Defined in Docker Compose but not built in CI:

* redhat: the public UBI repositories ship no bison/flex/dwarves,
  so the kernel cannot be built without a RHEL subscription

## archlinux

* [ArchWiki - Kernel_Arch Build System](https://wiki.archlinux.org/title/Kernel/Arch_Build_System)

## alpine

* [Docker Hub - Alpine](https://hub.docker.com/_/alpine)
* [Alpine Linux Wiki - Custom Kernel](https://wiki.alpinelinux.org/wiki/Custom_Kernel)

## azurelinux

* [microsoft/azurelinux](https://github.com/microsoft/azurelinux)
* [microsoft/CBL-Mariner-Linux-Kernel](https://github.com/microsoft/CBL-Mariner-Linux-Kernel)

## almalinux

* [CentOS - I Need to Build a Custom Kernel](https://wiki.centos.org/HowTos/Custom_Kernel)
* [Docker Hub - AlmaLinux](https://hub.docker.com/_/almalinux/)
* [Build Linux Kernel with CentOS 7](https://qiita.com/syo0901/items/3e03222bf4e79d22ccd1)

## gentoo

* [Gentoo Wiki - Kernel](https://wiki.gentoo.org/wiki/Kernel)
* [Gentoo Wiki - Kernel/Building from userspace](https://wiki.gentoo.org/wiki/Kernel/Building_from_userspace)
* [Gentoo Wiki - eclean](https://wiki.gentoo.org/wiki/Eclean/ja)
* [Gentoo Packages - app-portage/flaggie](https://packages.gentoo.org/packages/app-portage/flaggie)
* [gentoo/gentoo-docker-images](https://github.com/gentoo/gentoo-docker-images)
* [gg7/gentoo-kernel/guide](https://github.com/gg7/gentoo-kernel-guide)
* [jeekkd/gentoo-kernel-build](https://github.com/jeekkd/gentoo-kernel-build)

## linux-mint

* [Linux Mint](https://linuxmint.com/)
* [Linux Mint Installation Guide](https://linuxmint-installation-guide.readthedocs.io/en/latest/)
* [Upgrades](https://linuxmint-user-guide.readthedocs.io/en/latest/upgrade.html)
* [Upgrade Mint from command line? - Linux Mint Forums](https://forums.linuxmint.com/viewtopic.php?t=311267)

## ubuntu

* [Ubuntu - GitKernelBuild](https://wiki.ubuntu.com/KernelTeam/GitKernelBuild)
* [Ubuntu - BuildYourOwnKernel](https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel)
* [Debian - BuildADebianKernelPackage](https://wiki.debian.org/BuildADebianKernelPackage)
* [Ubuntuで最新のカーネルをお手軽にビルドする方法](https://gihyo.jp/admin/serial/01/ubuntu-recipe/0526?page=2)

## parrot

* [Parrot Security](https://parrotsec.org/)
* [Docker Hub - parrotsec/core](https://hub.docker.com/r/parrotsec/core)

## mageia

* [mageia - Official Image | Docker Hub](https://hub.docker.com/_/mageia)
* [Mageia wiki - URPMI](https://wiki.mageia.org/en/URPMI)
* [Mageia wiki - Installing and removing software](https://wiki.mageia.org/en/Installing_and_removing_software)
* [URPMI Package Management tool for Mageia System | 2DayGeek](https://www.2daygeek.com/urpmi-command-examples-manage-packages-mageia-system/)

