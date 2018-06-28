obj-m += gz_gpio.o
KDIR := /home/xuhangchang/firefly/kernel_310/kernel   #如果是用于arm平台，则内核路径为arm内核的路径

PWD = $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o
