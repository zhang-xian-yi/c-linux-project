#old Makefile use by linux kernel 
#obj-m := simpleDriver.o
#all :
#	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules     
#clean:
#	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 


#!/bin/bash
#通知编译器我们要编译模块的哪些源码
#这里是编译LinuxSimpleDriverZXY.c这个文件编译成中间文件LinuxSimpleDriverZXY.o
obj-m += zxy_vol_driver.o 
obj-m += zxy_led_driver.o
obj-m += zxy_adc_driver.o


#源码目录变量，这里用户需要根据实际情况选择路径
#将Linux的源码拷贝到目录/home/topeet/android4.0下并解压的
KDIR := /home/zhangxianyi/android4.0/iTop4412_Kernel_3.0

#当前目录变量
PWD ?= $(shell pwd)

#make命名默认寻找第一个目标
#make -C就是指调用执行的路径
#$(KDIR)Linux源码目录，作者这里指的是/home/topeet/android4.0/iTop4412_Kernel_3.0
#$(PWD)当前目录变量
#modules要执行的操作
all:
	make -C $(KDIR) M=$(PWD) modules
		
#make clean执行的操作是删除后缀为o的文件
clean:
	rm -rf *.o
	rm -rf zxy*
	rm -rf Mo*
	rm -rf m*
	rm -rf .zx*

