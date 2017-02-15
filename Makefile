obj-m:=process_list.o
KERNELDIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	insmod process_list.ko    
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rmmod process_list.ko
