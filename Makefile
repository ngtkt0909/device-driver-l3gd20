KPATH := $(HOME)/raspberrypi/linux
TPATH := $(HOME)/raspberrypi/tools
ARCH := arm
CROSS_COMPILE := $(TPATH)/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-
DOCS := ./doc

obj-m := ./src/i2c_l3gd20.o

.PHONY: all clean doc

all:
	make -C $(KPATH) M=$(PWD) modules ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	make -C $(KPATH) M=$(PWD) clean
	$(RM) $(DOCS)

install:
	sudo mkdir -p /lib/modules/`uname -r`/misc
	sudo cp ./src/i2c_l3gd20.ko /lib/modules/`uname -r`/misc
	sudo depmod -a

uninstall:
	sudo $(RM) /lib/modules/`uname -r`/misc/i2c_l3gd20.ko

connect:
	echo "i2c_l3gd20 0x6a" > /sys/bus/i2c/devices/i2c-1/new_device

disconnect:
	echo "0x6a" > /sys/bus/i2c/devices/i2c-1/delete_device
	modprobe -r i2c_l3gd20

doc:
	doxygen ./Doxyfile
