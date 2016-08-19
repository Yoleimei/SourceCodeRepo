#ifneq ($(KERNELRELEASE),)
obj-m := ModuleHello.o # target
modules-objs :=        # need 
#else
KERNELDIR := /usr/src/linux-headers-3.5.0-17
PWD := $(shell pwd)

.PHONY default:
#$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	make -C $(KERNELDIR) M=$(PWD) modules
#endif

