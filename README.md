# device-driver-l3gd20

## Overview
**Device driver for L3GD20**.
Can read 3-axis gyro sensors (dps).

## Install: Cross Compiling (for Raspberry Pi)
Build cross compilation environment
(refer to the [official documentation](https://www.raspberrypi.org/documentation/linux/kernel/building.md "link to KERNEL BUILDING") for details).

On 32bit Linux:
```shell
$ git clone --depth=1 https://github.com/raspberrypi/linux
$ git clone --depth=1 https://github.com/raspberrypi/tools
$ cd linux
$ KERNEL=kernel7
$ make ARCH=arm CROSS_COMPILE=../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf- bcm2709_defconfig
$ make ARCH=arm CROSS_COMPILE=../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf- zImage modules dtbs
```

On 64bit Linux:
```shell
$ git clone --depth=1 https://github.com/raspberrypi/linux
$ git clone --depth=1 https://github.com/raspberrypi/tools
$ cd linux
$ KERNEL=kernel7
$ make ARCH=arm CROSS_COMPILE=../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf- bcm2709_defconfig
$ make ARCH=arm CROSS_COMPILE=../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf- zImage modules dtbs
```

Change first and second lines of Makefile (**KPATH**, **TPATH**) according to download path on the previous step.

Make a kernel module (./src/l3gd20.ko):
```shell
$ make
```

Move the kernel module into the kernel directory and update module information:
```shell
$ sudo mkdir -p /lib/modules/`uname-r`/misc
$ sudo cp ./src/l3gd20.ko /lib/modules/`uname-r`/misc
$ sudo depmod -a
```

## Usage
Notify I2C device to the I2C core driver:
```shell
$ sudo -s
# echo "i2c_l3gd20 0x6a" > /sys/bus/i2c/devices/i2c-1/new_device
```

Remove I2C device:
```shell
$ sudo -s
# echo "0x6a" > /sys/bus/i2c/devices/i2c-1/delete_device
# modprobe -r i2c_l3gd20
```

## License
[MIT](https://github.com/ngtkt0909/device-driver-l3gd20/blob/master/LICENSE-MIT) and
[GPL](https://github.com/ngtkt0909/device-driver-l3gd20/blob/master/LICENSE-GPL)

## Author
[T. Ngtk](https://github.com/ngtkt0909)
