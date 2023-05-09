# build-kernel-rpm

```
$ docker build -t build-kernel-rpm .
$ docker run -it --rm -p 8000:8000 build-kernel-rpm
```
Borwse http://localhost:8000/ and you can get built rpm packages from `rpm` directory.

# reference

* [CentOS - I Need to Build a Custom Kernel](https://wiki.centos.org/HowTos/Custom_Kernel)
* [Docker Hub - AlmaLinux](https://hub.docker.com/_/almalinux/)
* [Build Linux Kernel with CentOS 7](https://qiita.com/syo0901/items/3e03222bf4e79d22ccd1)

