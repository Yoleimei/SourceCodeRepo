#ifneq ($(KERNELRELEASE),)
obj-m := hello.o # target
modules-objs :=        # need 
#else
KERNELDIR := /lib/modules/$(shell uname -r)/build 
PWD := $(shell pwd)

.PHONY default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
#endif

