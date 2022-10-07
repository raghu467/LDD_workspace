ARCH=arm
CROSS_COMPILE=arm-linux-gnueabihf-
K_DIR=/home/raghu/bbb_wp/LDD_workspace/source/linux
HOST_K_DIR=/lib/modules/$(shell uname -r)/build
obj-m=main.o

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)  -C $(K_DIR) M=$(PWD) modules


target:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)  -C $(K_DIR) M=$(PWD) modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)  -C $(K_DIR) M=$(PWD) clean

help:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)  -C $(K_DIR) M=$(PWD) help
 

host:
	make  -C $(HOST_K_DIR) M=$(PWD) modules
