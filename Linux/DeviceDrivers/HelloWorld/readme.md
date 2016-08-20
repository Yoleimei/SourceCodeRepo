01. How to compile a module
## begin of Makefile
obj-m := module-name.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
make -C $(KERNELDIR) M=$(PWD) modules
## end of Makefile

02. How do look up message of printk
dmesg




##### example #####
01. module_init / module_exit
sudo insmod hello.ko
sudo rmmod hello
dmesg | tail -n 9
02. module_param
sudo insmod hello.ko howmany=2 whom="yoleimei"
sudo rmmod hello
dmesg | tail -n 9
03. 

