obj-m += gz_adc.o
KDIR := /home/xuhangchang/firefly/kernel_44/kernel   #如果是用于arm平台，则内核路径为arm内核的路径

PWD = $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o
