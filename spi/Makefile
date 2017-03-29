HOME ?= /home/yourname
ARCH := arm
CROSS_COMPILE := $(HOME)/raspberry/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-
KPATH := $(HOME)/raspberry/linux

obj-m := ./src/spi_l3gd20.o

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KPATH) M=$(PWD)  modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KPATH) M=$(PWD) clean
