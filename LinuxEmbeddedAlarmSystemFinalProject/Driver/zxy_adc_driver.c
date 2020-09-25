/*模块信息相关头文件*/
#include <linux/init.h>
#include <linux/module.h>

/*驱动函数注册相关头文件*/
#include <linux/platform_device.h>

/*注册设备节点相关的头文件*/
#include <linux/miscdevice.h>
#include <linux/fs.h>

/*GPIO操作相关头文件*/
#include <linux/gpio.h>/*Linux中申请GPIO的头文件*/
#include <plat/gpio-cfg.h>/*三星平台的GPIO配置函数头文件*/
#include <mach/gpio.h>/*三星EXYNOS系列平台，GPIO配置参数宏定义头文件*/
#include <mach/gpio-exynos4.h>/*三星平台4412平台，GPIO宏定义头文件*/

/*ioremap函数头文件*/
#include <asm/io.h>

/*中断操作相关头文件*/
#include <linux/interrupt.h>
#include <linux/irq.h>

#include<linux/cdev.h>
#include<linux/wait.h>
#include<linux/sched.h>
#include<linux/uaccess.h>

/*模块相关协议申明*/
MODULE_LICENSE("Dual BSD/GPL");/*申明是开源的，没有内核版本限制*/
MODULE_AUTHOR("zhangxianyi");


/*驱动名和设备名宏定义*/
#define DRIVER_NAME "zxy_adc_ctl"
#define DEVICE_NAME "zxy_adc_ctl"

struct cdev adccdev;
static wait_queue_head_t wq;
dev_t devid;
static int have_data;
static int adc;


volatile unsigned long virt_addr_adc,phys_addr_adc;//用于存放ADC相关寄存器的虚拟地址和物理地址
volatile unsigned long *ADCCON,*ADCDLY,*ADCDAT,*CLRINTADC,*ADCMUX;

static irqreturn_t adc_interrupt(int irqno,void *dev)//中断处理函数
{
    have_data=1;//转换完成标志位
    writel(0x12,CLRINTADC);//清除中断标志位
    wake_up_interruptible(&wq);//唤醒等待队列
    return IRQ_HANDLED;
}

/*pwm地址操作初始化*/
static int adcinit(void)
{	
	/*指向对应的寄存器地址*/
	
	phys_addr_adc = 0x126C0000;
	virt_addr_adc = (unsigned long)ioremap(phys_addr_adc,0x20);
	ADCCON = (unsigned long*)(virt_addr_adc+0x00);
	ADCDLY = (unsigned long*)(virt_addr_adc+0x08);
	ADCDAT = (unsigned long*)(virt_addr_adc+0x0C);
	CLRINTADC = (unsigned long*)(virt_addr_adc+0x18);
	ADCMUX = (unsigned long*)(virt_addr_adc+0x1C);
	
	request_irq(IRQ_ADC,adc_interrupt,IRQF_DISABLED,"adc1",NULL);//申请中断
	
	init_waitqueue_head(&wq);//初始化等待队列
    return 0;
}

//static ssize_t adc_read(struct file *filep,char __user *buf,size_t len, loff_t *pos)
static ssize_t adc_read(struct file *filep)
{
    printk(KERN_EMERG "beging read\n");
	writel(0x0,ADCMUX);//选择转换通道
    writel(1<<0|1<<16|1<<14|65<<6,ADCCON);//启动12位AD转换
    wait_event_interruptible(wq,have_data==1);//进入等待队列
    adc = readl(ADCDAT)&0xfff;
    have_data=0;
    return adc;
}


/*IO操作执行的功能函数*/

static long zxy_adc_ioctl( struct file *files, unsigned int cmd, unsigned long arg)
{
    printk(KERN_EMERG "zxy_adc dev ioctl\n");
    return 0;
}

/*设备节点移除时的执行函数*/

static int zxy_adc_release(struct inode *inode, struct file *file){
	printk(KERN_EMERG "zxy_adc dev release\n");
	return 0;
}
/*设备节点打开成功后的执行函数*/
static int zxy_adc_open(struct inode *inode, struct file *file){
	printk(KERN_EMERG "zxy_adc dev open\n");
	return 0;
}
/*设备节点可设备可实现的操作函数*/
static struct file_operations zxy_adc_ops = {
	.owner = THIS_MODULE,
	.open = zxy_adc_open,
	.read = adc_read,
	.release = zxy_adc_release,
	.unlocked_ioctl = zxy_adc_ioctl,
};
/*设备节点的结构体实现*/
static  struct miscdevice zxy_adc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &zxy_adc_ops,
};
/*驱动注册成功后的执行函数*/
static int zxy_adc_probe(struct platform_device *pdv){
    adcinit();
	misc_register(&zxy_adc_dev);/*设备节点注册：杂项设备*/
	return 0;
}

/*驱动退出时的执行函数*/
static int zxy_adc_remove(struct platform_device *pdv){
	printk(KERN_EMERG "\tremove\n");
	/*在这里添加要实现的操作*/
	misc_deregister(&zxy_adc_dev); /*设备节点移除：杂项设备*/
	return 0;
}

/*驱动shutdown时的执行函数*/
static void zxy_adc_shutdown(struct platform_device *pdv){
	/*在这里添加要实现的操作*/
	
}

/*驱动suspend时的执行函数*/
static int zxy_adc_suspend(struct platform_device *pdv,pm_message_t pmt){
	/*在这里添加要实现的操作*/
	return 0;
}

/*驱动resume时的执行函数*/
static int zxy_adc_resume(struct platform_device *pdv){
	/*在这里添加要实现的操作*/
	return 0;
}

/*驱动注册函数参数的结构体实现*/
struct platform_driver zxy_adc_driver = {
	.probe = zxy_adc_probe,
	.remove = zxy_adc_remove,
	.shutdown = zxy_adc_shutdown,
	.suspend = zxy_adc_suspend,
	.resume = zxy_adc_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	}
};
/*驱动入口函数实现*/
static int zxy_adc_init(void)
{
	int DriverState;
	printk(KERN_EMERG " zxy_adc enter!\n");
	DriverState = platform_driver_register(&zxy_adc_driver);/*驱动函数注册*/
	printk(KERN_EMERG "\tDriverState is %d\n",DriverState);
	return 0;
}

/*驱动出口函数实现*/

static void zxy_adc_exit(void)
{
	printk(KERN_EMERG "zxy_adc exit!\n");
	platform_driver_unregister(&zxy_adc_driver);	/*驱动函数注销*/
}

/*模块入口函数&出口函数*/
module_init(zxy_adc_init);
module_exit(zxy_adc_exit);




