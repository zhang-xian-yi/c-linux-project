#定义 标准文件接口 的宏
DEFS := -D_POSIX_SOURCE

#定义编译命令
CC := arm-none-linux-gnueabi-gcc

#定义清除命令
RM := rm -rf 

#header file
HEADER_PATH := -I./include

#定义标签
CFLAGS := -Wall -c

#定义链接库文件
LIBS := 

LIB_PATH := 

#
VERSION := 1.01
FLAG := elf

#定义目标
TARGET := alarm_system_$(VERSION).$(FLAG)

#获取所有 当前列表下的c 文件
SRC = $(wildcard *.c)

#转换所有c文件 为对象文件
OBJS = $(patsubst %.c,%.o,${SRC})

# 目标: 依赖文件 以及命令

$(TARGET):$(OBJS)  
	$(CC) $^ -o $@ $(LIB_PATH) $(LIBS) -static  

$(OBJS):%.o : %.c  
	$(CC) $(DEFS) $(CFLAGS) $^ -o $@ $(HEADER_PATH)    

.PHONY:clean
clean:
	$(RM) $(TARGET) $(OBJS)
