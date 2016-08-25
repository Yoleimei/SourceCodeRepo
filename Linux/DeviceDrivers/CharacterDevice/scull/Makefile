#ifneq ($(KERNELRELEASE),)
obj-m := scull.o       # target
modules-objs :=        # need 
#else
KERNELDIR := /lib/modules/$(shell uname -r)/build 
PWD := $(shell pwd)

.PHONY default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
#endif

