/*ģ����Ϣ���ͷ�ļ�*/
#include <linux/init.h>
#include <linux/module.h>

/*��������ע�����ͷ�ļ�*/
#include <linux/platform_device.h>

/*ע���豸�ڵ���ص�ͷ�ļ�*/
#include <linux/miscdevice.h>
#include <linux/fs.h>

/*GPIO�������ͷ�ļ�*/
#include <linux/gpio.h>/*Linux������GPIO��ͷ�ļ�*/
#include <plat/gpio-cfg.h>/*����ƽ̨��GPIO���ú���ͷ�ļ�*/
#include <mach/gpio.h>/*����EXYNOSϵ��ƽ̨��GPIO���ò����궨��ͷ�ļ�*/
#include <mach/gpio-exynos4.h>/*����ƽ̨4412ƽ̨��GPIO�궨��ͷ�ļ�*/

/*ioremap����ͷ�ļ�*/
#include <asm/io.h>

/*�жϲ������ͷ�ļ�*/
#include <linux/interrupt.h>
#include <linux/irq.h>

#include<linux/cdev.h>
#include<linux/wait.h>
#include<linux/sched.h>
#include<linux/uaccess.h>

/*ģ�����Э������*/
MODULE_LICENSE("Dual BSD/GPL");/*�����ǿ�Դ�ģ�û���ں˰汾����*/
MODULE_AUTHOR("zhangxianyi");


/*���������豸���궨��*/
#define DRIVER_NAME "zxy_adc_ctl"
#define DEVICE_NAME "zxy_adc_ctl"

struct cdev adccdev;
static wait_queue_head_t wq;
dev_t devid;
static int have_data;
static int adc;


volatile unsigned long virt_addr_adc,phys_addr_adc;//���ڴ��ADC��ؼĴ����������ַ�������ַ
volatile unsigned long *ADCCON,*ADCDLY,*ADCDAT,*CLRINTADC,*ADCMUX;

static irqreturn_t adc_interrupt(int irqno,void *dev)//�жϴ�����
{
    have_data=1;//ת����ɱ�־λ
    writel(0x12,CLRINTADC);//����жϱ�־λ
    wake_up_interruptible(&wq);//���ѵȴ�����
    return IRQ_HANDLED;
}

/*pwm��ַ������ʼ��*/
static int adcinit(void)
{	
	/*ָ���Ӧ�ļĴ�����ַ*/
	
	phys_addr_adc = 0x126C0000;
	virt_addr_adc = (unsigned long)ioremap(phys_addr_adc,0x20);
	ADCCON = (unsigned long*)(virt_addr_adc+0x00);
	ADCDLY = (unsigned long*)(virt_addr_adc+0x08);
	ADCDAT = (unsigned long*)(virt_addr_adc+0x0C);
	CLRINTADC = (unsigned long*)(virt_addr_adc+0x18);
	ADCMUX = (unsigned long*)(virt_addr_adc+0x1C);
	
	request_irq(IRQ_ADC,adc_interrupt,IRQF_DISABLED,"adc1",NULL);//�����ж�
	
	init_waitqueue_head(&wq);//��ʼ���ȴ�����
    return 0;
}

//static ssize_t adc_read(struct file *filep,char __user *buf,size_t len, loff_t *pos)
static ssize_t adc_read(struct file *filep)
{
    printk(KERN_EMERG "beging read\n");
	writel(0x0,ADCMUX);//ѡ��ת��ͨ��
    writel(1<<0|1<<16|1<<14|65<<6,ADCCON);//����12λADת��
    wait_event_interruptible(wq,have_data==1);//����ȴ�����
    adc = readl(ADCDAT)&0xfff;
    have_data=0;
    return adc;
}


/*IO����ִ�еĹ��ܺ���*/

static long zxy_adc_ioctl( struct file *files, unsigned int cmd, unsigned long arg)
{
    printk(KERN_EMERG "zxy_adc dev ioctl\n");
    return 0;
}

/*�豸�ڵ��Ƴ�ʱ��ִ�к���*/

static int zxy_adc_release(struct inode *inode, struct file *file){
	printk(KERN_EMERG "zxy_adc dev release\n");
	return 0;
}
/*�豸�ڵ�򿪳ɹ����ִ�к���*/
static int zxy_adc_open(struct inode *inode, struct file *file){
	printk(KERN_EMERG "zxy_adc dev open\n");
	return 0;
}
/*�豸�ڵ���豸��ʵ�ֵĲ�������*/
static struct file_operations zxy_adc_ops = {
	.owner = THIS_MODULE,
	.open = zxy_adc_open,
	.read = adc_read,
	.release = zxy_adc_release,
	.unlocked_ioctl = zxy_adc_ioctl,
};
/*�豸�ڵ�Ľṹ��ʵ��*/
static  struct miscdevice zxy_adc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &zxy_adc_ops,
};
/*����ע��ɹ����ִ�к���*/
static int zxy_adc_probe(struct platform_device *pdv){
    adcinit();
	misc_register(&zxy_adc_dev);/*�豸�ڵ�ע�᣺�����豸*/
	return 0;
}

/*�����˳�ʱ��ִ�к���*/
static int zxy_adc_remove(struct platform_device *pdv){
	printk(KERN_EMERG "\tremove\n");
	/*���������Ҫʵ�ֵĲ���*/
	misc_deregister(&zxy_adc_dev); /*�豸�ڵ��Ƴ��������豸*/
	return 0;
}

/*����shutdownʱ��ִ�к���*/
static void zxy_adc_shutdown(struct platform_device *pdv){
	/*���������Ҫʵ�ֵĲ���*/
	
}

/*����suspendʱ��ִ�к���*/
static int zxy_adc_suspend(struct platform_device *pdv,pm_message_t pmt){
	/*���������Ҫʵ�ֵĲ���*/
	return 0;
}

/*����resumeʱ��ִ�к���*/
static int zxy_adc_resume(struct platform_device *pdv){
	/*���������Ҫʵ�ֵĲ���*/
	return 0;
}

/*����ע�ắ�������Ľṹ��ʵ��*/
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
/*������ں���ʵ��*/
static int zxy_adc_init(void)
{
	int DriverState;
	printk(KERN_EMERG " zxy_adc enter!\n");
	DriverState = platform_driver_register(&zxy_adc_driver);/*��������ע��*/
	printk(KERN_EMERG "\tDriverState is %d\n",DriverState);
	return 0;
}

/*�������ں���ʵ��*/

static void zxy_adc_exit(void)
{
	printk(KERN_EMERG "zxy_adc exit!\n");
	platform_driver_unregister(&zxy_adc_driver);	/*��������ע��*/
}

/*ģ����ں���&���ں���*/
module_init(zxy_adc_init);
module_exit(zxy_adc_exit);




