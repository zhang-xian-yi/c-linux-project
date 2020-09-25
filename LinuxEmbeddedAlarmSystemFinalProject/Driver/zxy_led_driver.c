#include <linux/init.h>
#include <linux/module.h>

/*驱动注册的头文件，包含驱动的结构体和注册和卸载的函数*/
#include <linux/platform_device.h>
/*注册杂项设备头文件*/
#include <linux/miscdevice.h>
/*注册设备节点的文件结构体*/
#include <linux/fs.h>

/*Linux中申请GPIO的头文件*/
#include <linux/gpio.h>
/*三星平台的GPIO配置函数头文件*/
/*三星平台EXYNOS系列平台，GPIO配置参数宏定义头文件*/
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>
/*三星平台4412平台，GPIO宏定义头文件*/
#include <mach/gpio-exynos4.h>

#define DRIVER_NAME "zxy_led_ctl"
#define DEVICE_NAME "zxy_led_ctl"


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("zhangxianyi");

/*****************************************************************************
*   Prototype    : zxyDriver_ioctl
*   Description  : zxy driver io control
*   Input        : struct file *files  
*                  unsigned int cmd    
*                  unsigned long arg   
*   Output       : None
*   Return Value : static long
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static long zxyDriver_ioctl( struct file *files, unsigned int cmd, unsigned long arg)
{
	printk("cmd is %d,arg is %d\n",cmd,arg);
	if(cmd > 1)
    {
		printk(KERN_EMERG "cmd is 0 or 1\n");
	}
	if(arg > 3)
    {
		printk(KERN_EMERG "arg is only 1 or 2\n");
	}
    
	switch(arg)
    {
		case 1: gpio_set_value(EXYNOS4_GPL2(0),cmd);break;
		case 2: gpio_set_value(EXYNOS4_GPK1(1),cmd);break;
		default: break;
	}
	return 0;
}

/*****************************************************************************
*   Prototype    : zxyDriver_release
*   Description  : realse zxy driver 
*   Input        : struct inode *inode  
*                  struct file *file    
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static int zxyDriver_release(struct inode *inode, struct file *file){
	printk(KERN_EMERG "release the zxy driver control\n");
	return 0;
}
/*****************************************************************************
*   Prototype    : zxyDriver_open
*   Description  : open the zxy driver control
*   Input        : struct inode *inode  
*                  struct file *file    
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static int zxyDriver_open(struct inode *inode, struct file *file){
	printk(KERN_EMERG "open zxy driver control\n");
	return 0;
}


static struct file_operations zxyDriver_ops = {
	.owner = THIS_MODULE,
	.open = zxyDriver_open,
	.release = zxyDriver_release,
	.unlocked_ioctl = zxyDriver_ioctl,
};

static  struct miscdevice zxyDriver_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &zxyDriver_ops,
};

/*****************************************************************************
*   Prototype    : zxyDriver_probe
*   Description  : zxy driver control probe init the zxy control
*   Input        : struct platform_device *pdv  
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static int zxyDriver_probe(struct platform_device *pdv){
	int ret;
	
	printk(KERN_EMERG "\tinitialized\n");
	
	ret = gpio_request(EXYNOS4_GPL2(0),"zxy_led_ctl");
	if(ret < 0){
		printk(KERN_EMERG "gpio_request EXYNOS4_GPL2(0) failed!\n");
		return ret;
	}
	ret = gpio_request(EXYNOS4_GPK1(1),"zxy_led_ctl");
	if(ret < 0){
		printk(KERN_EMERG "gpio_request EXYNOS4_GPK1(1) failed!\n");
		return ret;
	}
	s3c_gpio_cfgpin(EXYNOS4_GPK1(1),S3C_GPIO_OUTPUT);	
	gpio_set_value(EXYNOS4_GPK1(1),0);
	s3c_gpio_cfgpin(EXYNOS4_GPL2(0),S3C_GPIO_OUTPUT);	
	gpio_set_value(EXYNOS4_GPL2(0),0);
    
	misc_register(&zxyDriver_dev);
	return 0;
}
/*****************************************************************************
*   Prototype    : zxyDriver_remove
*   Description  : remove the node zxy driver control
*   Input        : struct platform_device *pdv  
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static int zxyDriver_remove(struct platform_device *pdv){
	printk(KERN_EMERG "\tremove\n");
	misc_deregister(&zxyDriver_dev);
	return 0;
}
/*****************************************************************************
*   Prototype    : zxyDriver_shutdown
*   Description  : shutdown zxy deiver
*   Input        : struct platform_device *pdv  
*   Output       : None
*   Return Value : static void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static void zxyDriver_shutdown(struct platform_device *pdv){
	
}
/*****************************************************************************
*   Prototype    : zxyDriver_suspend
*   Description  : suspend the zxy driver
*   Input        : struct platform_device *pdv  
*                  pm_message_t pmt             
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static int zxyDriver_suspend(struct platform_device *pdv,pm_message_t pmt){
	
	return 0;
}
/*****************************************************************************
*   Prototype    : zxyDriver_resume
*   Description  : resume the zxy driver
*   Input        : struct platform_device *pdv  
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static int zxyDriver_resume(struct platform_device *pdv){
	
	return 0;
}
/*define the platform_driver struct and init the value*/
struct platform_driver zxyDriver_driver = {
	.probe = zxyDriver_probe,
	.remove = zxyDriver_remove,
	.shutdown = zxyDriver_shutdown,
	.suspend = zxyDriver_suspend,
	.resume = zxyDriver_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	}
};

/*****************************************************************************
*   Prototype    : zxyDriver_init
*   Description  : static init the zxy Driver control
*   Input        : void  
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static int zxyDriver_init(void)
{
	int DriverState;
	printk(KERN_EMERG "hello zxy driver ctl enter!\n");
	DriverState = platform_driver_register(&zxyDriver_driver);
	printk(KERN_EMERG "\tDriverState is %d\n",DriverState);
	return 0;
}

/*****************************************************************************
*   Prototype    : zxyDriver_exit
*   Description  : exit the zxy Driver
*   Input        : void  
*   Output       : None
*   Return Value : static void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/15
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static void zxyDriver_exit(void)
{
	printk(KERN_EMERG "bye zxy_ctl kernel exit!\n");
	
	platform_driver_unregister(&zxyDriver_driver);	
}

/*module register the function*/
module_init(zxyDriver_init);
module_exit(zxyDriver_exit);




