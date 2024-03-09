.PHONY:	build run

build:	base.txz
	docker build -t chimera .
	rm base.txz

run:
	docker run -it chimera bash

BASE_URL=https://repo.chimera-linux.org/live/20221115/chimera-linux-x86_64-ROOTFS-20221115-core.tar.gz
BASE_URL=https://repo.chimera-linux.org/live/20230305/chimera-linux-x86_64-ROOTFS-20230305-core.tar.gz
BASE_URL=https://repo.chimera-linux.org/live/20230611/chimera-linux-x86_64-ROOTFS-20230611-full.tar.gz
BASE_URL=https://repo.chimera-linux.org/live/20230915/chimera-linux-x86_64-ROOTFS-20230915-full.tar.gz
BASE_URL=https://repo.chimera-linux.org/live/20231227/chimera-linux-x86_64-ROOTFS-20231227-full.tar.gz
BASE_URL=https://repo.chimera-linux.org/live/20240122/chimera-linux-x86_64-ROOTFS-20240122-full.tar.gz

base.txz:
	# wget   -O base.txz $(BASE_URL)
	aria2c -o base.txz $(BASE_URL)

