KPATH := $(HOME)/raspberrypi/linux
TPATH := $(HOME)/raspberrypi/tools
ARCH := arm
CROSS_COMPILE := $(TPATH)/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-
DOCS := ./doc

obj-m := ./src/l3gd20.o

.PHONY: all clean doc

all:
	make -C $(KPATH) M=$(PWD) modules ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	make -C $(KPATH) M=$(PWD) clean
	$(RM) $(DOCS)

doc:
	doxygen ./Doxyfile
