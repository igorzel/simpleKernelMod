obj-m := algo_kernel_mod.o

KDIR := /usr/src/linux-headers-$(shell uname -r)
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.mod.c *.o *.ko *.order *.symvers .*.cmd
