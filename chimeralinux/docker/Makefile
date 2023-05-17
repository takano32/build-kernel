
.PHONY:	build run

build:	base.txz
	docker build -t chimera .
	rm base.txz

run:
	docker run -it chimera bash

BASE_URL=https://repo.chimera-linux.org/live/20221115/chimera-linux-x86_64-ROOTFS-20221115-core.tar.gz
BASE_URL=https://repo.chimera-linux.org/live/20230305/chimera-linux-x86_64-ROOTFS-20230305-core.tar.gz

base.txz:
	wget -O base.txz $(BASE_URL)

