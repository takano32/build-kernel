# build-kernel

```
$ docker build -t build-kernel .
$ docker run -it --rm -p 8000:8000 build-kernel
```
Borwse http://localhost:8000/ and you can get built debian packages from `dpkg` directory.

# reference

* [Ubuntu - GitKernelBuild](https://wiki.ubuntu.com/KernelTeam/GitKernelBuild)
* [Ubuntu - BuildYourOwnKernel](https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel)
* [Debian - BuildADebianKernelPackage](https://wiki.debian.org/BuildADebianKernelPackage)
* [Ubuntuで最新のカーネルをお手軽にビルドする方法](https://gihyo.jp/admin/serial/01/ubuntu-recipe/0526?page=2)

