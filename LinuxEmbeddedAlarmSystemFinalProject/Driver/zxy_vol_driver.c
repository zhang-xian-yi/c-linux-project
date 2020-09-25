#include <linux/init.h>
#include <linux/module.h>

/*驱动注册的头文件，包含驱动的结构体和注册和卸载的函数*/
#include <linux/platform_device.h>
/*注册杂项设备头文??*/
#include <linux/miscdevice.h>
/*注册设备节点的文件结构体*/
#include <linux/fs.h>

/*Linux中申请GPIO的头文件*/
#include <linux/gpio.h>
/*三星平台的GPIO配置函数头文??*/
/*三星平台EXYNOS系列平台，GPIO配置参数宏定义头文件*/
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

/*三星平台4412平台，GPIO宏定义头文件*/
#include <mach/gpio-exynos4.h>

/*中断操作相关头文??*/
#include <linux/interrupt.h>
#include <linux/irq.h>

//延时函数头文??
#include <linux/delay.h>

//驱动名称
#define DRIVER_NAME "zxy_vol_ctl"
#define DEVICE_NAME "zxy_vol_ctl"


//模块相关协议声明
MODULE_LICENSE("Dual BSD/GPL");/*申明是开源的，没有内核版本限??*/
MODULE_AUTHOR("zhangxianyi");

//VOL+ --->GPX2_1----->EXINT17
//VOL- --->GPX2_0----->EXINT16

//LED2--->GPL2_0
//LED3--->GPk1_1

//申请寄存??-->配置寄存器为复用中断功能-->设置为上??-->中断注册-->中断实现函数

static int status_flag = 0;

#define vol1_down 1
#define vol2_down 2

//VOL+中断实现函数  VOL+按下时，LED2实现翻转
static irqreturn_t eint17_interrupt_handler(int irq, void *dev_id) {
		printk("vol+ is pressed!\n");
        status_flag = vol1_down;                
        return IRQ_HANDLED;
}
//VOL-中断实现函数
static irqreturn_t eint16_interrupt_handler(int irq, void *dev_id) {
        printk("vol- is pressed!\n");
        status_flag = vol2_down;
        return IRQ_HANDLED;
}

/*驱动??出时的执行函??*/
static int zxy_remove(struct platform_device *pdv)
{	
	printk(KERN_EMERG "\ tremove \n");
    //gpio 的释??
	gpio_free(EXYNOS4_GPX2(1));
	gpio_free(EXYNOS4_GPX2(0));
	return 0;
}
/*驱动shutdown时的执行函数*/
static void zxy_shutdown(struct platform_device *pdv)
{	
	return;
}
/*驱动suspend时的执行函数*/
static int zxy_suspend(struct platform_device *pdv,pm_message_t pmt){
	
	return 0;
}
/*驱动resume时的执行函数*/
static int zxy_resume(struct platform_device *pdv){
	
	return 0;
}

static ssize_t vol_read(struct file *filep)
{
    printk("....vol get the value:  \n");
    printk("....read flag %d\n",status_flag);
    return status_flag;
}


static struct file_operations zxy_vol_driver_ops = {
	.owner = THIS_MODULE,
    .read = vol_read,
};

static  struct miscdevice zxyDriver_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &zxy_vol_driver_ops,
};


static int zxy_probe(struct platform_device *pdv)
{
	int ret;
	printk(KERN_EMERG "\t initialized \n");	
	//VOL+链接的端口GPX2_1，申请寄存器-->配置寄存器为复用中断功能-->设置为上??-->
	ret = gpio_request(EXYNOS4_GPX2(1),"VOL+");
    if(ret<0)
    {
		printk("gpio request failed!\n");
		return ret;
	}
	s3c_gpio_cfgpin(EXYNOS4_GPX2(1),S3C_GPIO_SFN(0xF));
	s3c_gpio_setpull(EXYNOS4_GPX2(1), S3C_GPIO_PULL_UP);
	//VOL-链接的端口GPX2_0，申请寄存器-->配置寄存器为复用中断功能-->设置为上??-->
	ret = gpio_request(EXYNOS4_GPX2(0),"VOL-");
    if(ret<0){
		printk("gpio request failed!\n");
		return ret;
	}
	s3c_gpio_cfgpin(EXYNOS4_GPX2(0),S3C_GPIO_SFN(0xF));
	s3c_gpio_setpull(EXYNOS4_GPX2(0), S3C_GPIO_PULL_UP);
	
	//中断注册
	ret = request_irq(IRQ_EINT(17),eint17_interrupt_handler,IRQ_TYPE_EDGE_FALLING,"eint17",pdv);
	if( ret < 0 ){
		printk("zxy + ctl request failed!\n");
		return 0;
	}
	ret = request_irq(IRQ_EINT(16),eint16_interrupt_handler,IRQ_TYPE_EDGE_FALLING,"eint16",pdv);
	if( ret < 0 ){
		printk("zxy -ctl failed!\n");
		return 0;
	}
    
    //注册 设备节点
    misc_register(&zxyDriver_dev);
	return 0;
}


/*驱动注册函数参数的结构体实现*/
struct platform_driver zxy_vol_driver = {
	.probe = zxy_probe,
	.remove = zxy_remove,
	.shutdown = zxy_shutdown,
	.suspend = zxy_suspend,
	.resume = zxy_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	}
};



/*驱动入口函数实现*/
static int zxy_init(void)
{
	int DriverState;	
	printk(KERN_EMERG "zxy init enter!\n");
	DriverState = platform_driver_register(&zxy_vol_driver);
	printk(KERN_EMERG "\tDriverState is %d\n",DriverState);
	return 0;
}



/*驱动出口函数实现*/
static void zxy_exit(void)
{
	printk(KERN_EMERG "zxy ctl exit exit!\n");
	platform_driver_unregister(&zxy_vol_driver);	
}


/*模块入口函数&出口函数*/
module_init(zxy_init);
module_exit(zxy_exit); 

