#include <linux/init.h>
#include <linux/module.h>

/*����ע���ͷ�ļ������������Ľṹ���ע���ж�صĺ���*/
#include <linux/platform_device.h>
/*ע�������豸ͷ��??*/
#include <linux/miscdevice.h>
/*ע���豸�ڵ���ļ��ṹ��*/
#include <linux/fs.h>

/*Linux������GPIO��ͷ�ļ�*/
#include <linux/gpio.h>
/*����ƽ̨��GPIO���ú���ͷ��??*/
/*����ƽ̨EXYNOSϵ��ƽ̨��GPIO���ò����궨��ͷ�ļ�*/
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

/*����ƽ̨4412ƽ̨��GPIO�궨��ͷ�ļ�*/
#include <mach/gpio-exynos4.h>

/*�жϲ������ͷ��??*/
#include <linux/interrupt.h>
#include <linux/irq.h>

//��ʱ����ͷ��??
#include <linux/delay.h>

//��������
#define DRIVER_NAME "zxy_vol_ctl"
#define DEVICE_NAME "zxy_vol_ctl"


//ģ�����Э������
MODULE_LICENSE("Dual BSD/GPL");/*�����ǿ�Դ�ģ�û���ں˰汾��??*/
MODULE_AUTHOR("zhangxianyi");

//VOL+ --->GPX2_1----->EXINT17
//VOL- --->GPX2_0----->EXINT16

//LED2--->GPL2_0
//LED3--->GPk1_1

//����Ĵ�??-->���üĴ���Ϊ�����жϹ���-->����Ϊ��??-->�ж�ע��-->�ж�ʵ�ֺ���

static int status_flag = 0;

#define vol1_down 1
#define vol2_down 2

//VOL+�ж�ʵ�ֺ���  VOL+����ʱ��LED2ʵ�ַ�ת
static irqreturn_t eint17_interrupt_handler(int irq, void *dev_id) {
		printk("vol+ is pressed!\n");
        status_flag = vol1_down;                
        return IRQ_HANDLED;
}
//VOL-�ж�ʵ�ֺ���
static irqreturn_t eint16_interrupt_handler(int irq, void *dev_id) {
        printk("vol- is pressed!\n");
        status_flag = vol2_down;
        return IRQ_HANDLED;
}

/*����??��ʱ��ִ�к�??*/
static int zxy_remove(struct platform_device *pdv)
{	
	printk(KERN_EMERG "\ tremove \n");
    //gpio ����??
	gpio_free(EXYNOS4_GPX2(1));
	gpio_free(EXYNOS4_GPX2(0));
	return 0;
}
/*����shutdownʱ��ִ�к���*/
static void zxy_shutdown(struct platform_device *pdv)
{	
	return;
}
/*����suspendʱ��ִ�к���*/
static int zxy_suspend(struct platform_device *pdv,pm_message_t pmt){
	
	return 0;
}
/*����resumeʱ��ִ�к���*/
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
	//VOL+���ӵĶ˿�GPX2_1������Ĵ���-->���üĴ���Ϊ�����жϹ���-->����Ϊ��??-->
	ret = gpio_request(EXYNOS4_GPX2(1),"VOL+");
    if(ret<0)
    {
		printk("gpio request failed!\n");
		return ret;
	}
	s3c_gpio_cfgpin(EXYNOS4_GPX2(1),S3C_GPIO_SFN(0xF));
	s3c_gpio_setpull(EXYNOS4_GPX2(1), S3C_GPIO_PULL_UP);
	//VOL-���ӵĶ˿�GPX2_0������Ĵ���-->���üĴ���Ϊ�����жϹ���-->����Ϊ��??-->
	ret = gpio_request(EXYNOS4_GPX2(0),"VOL-");
    if(ret<0){
		printk("gpio request failed!\n");
		return ret;
	}
	s3c_gpio_cfgpin(EXYNOS4_GPX2(0),S3C_GPIO_SFN(0xF));
	s3c_gpio_setpull(EXYNOS4_GPX2(0), S3C_GPIO_PULL_UP);
	
	//�ж�ע��
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
    
    //ע�� �豸�ڵ�
    misc_register(&zxyDriver_dev);
	return 0;
}


/*����ע�ắ�������Ľṹ��ʵ��*/
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



/*������ں���ʵ��*/
static int zxy_init(void)
{
	int DriverState;	
	printk(KERN_EMERG "zxy init enter!\n");
	DriverState = platform_driver_register(&zxy_vol_driver);
	printk(KERN_EMERG "\tDriverState is %d\n",DriverState);
	return 0;
}



/*�������ں���ʵ��*/
static void zxy_exit(void)
{
	printk(KERN_EMERG "zxy ctl exit exit!\n");
	platform_driver_unregister(&zxy_vol_driver);	
}


/*ģ����ں���&���ں���*/
module_init(zxy_init);
module_exit(zxy_exit); 

