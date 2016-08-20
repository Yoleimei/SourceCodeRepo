01. How to compile a module
## begin of Makefile
obj-m := module-name.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
make -C $(KERNELDIR) M=$(PWD) modules
## end of Makefile

02. How do look up message of printk
dmesg

