#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/ioctl.h>
/*增加串口操作相关头文件*/
#include <termios.h>

#include "alarmctl.h"

#define __NO_VERSION__

/*设置串口参数：波特率、数据位、校验位、停止位*/
int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio, oldtio;						//新旧termios结构体变量
	if(tcgetattr(fd, &oldtio) != 0)						//读取当前参数
	{
		perror("SetupSerial 1");
		return -1;
	}
	
	//新的结构体变量设置--就是对一个新结构清零初始化
	bzero(&newtio, sizeof(newtio));						//将新结构体置零
	newtio.c_cflag |= CLOCAL | CREAD;					//通常同时使能，确保程序不被其他端口控制和信号干扰，同时串口驱动将读取进入的数据。
	newtio.c_cflag &= ~CSIZE;							//数据位清0
	
	switch(nBits)				//设置数据位--其他位自己设置
	{
		case 7:
			newtio.c_cflag |= CS7;						//七位
			break;
		case 8:
			newtio.c_cflag |= CS8;						//八位
			break;
	}
	
	switch(nEvent)				//设置奇偶校验
	{
		case 'O'://奇校验
			newtio.c_cflag |= PARENB;					//允许校验位
			newtio.c_cflag |= PARODD;					//使用奇校验(清除该标志表示使用偶校验)
			newtio.c_iflag |= (INPCK | ISTRIP);			//启用极性 + 剥去第八位
			break;
		case 'E'://偶校验
			newtio.c_cflag |= PARENB;					//允许校验位
			newtio.c_cflag &= ~PARODD;					//使用偶校验(清除该标志表示使用偶校验)
			newtio.c_iflag |= (INPCK | ISTRIP);			//启用极性 + 剥去第八位
			break;
		case 'N'://无校验
			newtio.c_cflag &= ~PARENB;					//无校验
			break;
	}
	
	switch(nSpeed)				//设置传输速度
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	
	if(nStop == 1)				//设置停止位
	{
		newtio.c_cflag &= ~CSTOPB;						//一位停止位
	}
	else if(nStop == 2)
	{
		newtio.c_cflag |= CSTOPB;						//两位停止位
	}
	//如果VTIME=0，VMIN=0，不管能否读取到数据，read都会立即返回
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd, TCIFLUSH);								//清除所有正在发生的I/O 数据
	//设置生效
	if((tcsetattr(fd, TCSANOW, &newtio)) != 0)			//不等数据传输完毕就立即改变属性
	{
		perror("com set error");
		return -1;
	}
	
	return 0;
}


/*串口写数据*/
/*****************************************************************************
*   Prototype    : write_UART1
*   Description  : write the data to uart1
*   Input        : int fd        
*                  char *write1  
*                  int i         
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/21
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int write_UART1(int fd,char *write1,int i)//fd:设备；write1：写的内容;i:写数据次数
{
	int w_length;
	while(i--)
	{
		w_length = write(fd, write1, strlen(write1));
		if(w_length < 0)
		{
			printf("Write buffer error!!!\n");
			exit(1);
		}
		else
		{
			printf("Having writing %d byte.\n",w_length);
			sleep(1);
		}
	}	
	return 0;
}

/*串口读数据*/
/*****************************************************************************
*   Prototype    : read_UART1
*   Description  : read the data from uart1
*   Input        : int fd  
*   Output       : None
*   Return Value : char *
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/21
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
char * read_UART1(int fd)
{
	int nByte;
	char buffer[512];
	char buffer1[512];
	char *buffer2;
	
	memset(buffer, 0, sizeof(buffer));
	memset(buffer1, 0, sizeof(buffer1));
	/*如果串口读到数据,则开始接收串口收到的数据*/
	while((nByte = read(fd, buffer, 512))>0)
	{
		buffer[nByte+1] = '\0';//在数据后加结束符
	}
    memcpy(buffer1,buffer,strlen(buffer));//复制一份值
	write(fd,buffer,strlen(buffer));//把接收到的发送回去
	write(fd,buffer1,strlen(buffer1));//把接收到的发送回去
	memset(buffer, 0, strlen(buffer));//将接受buffer清空
	nByte = 0;
	buffer2 = buffer1;
	//printf("buffer1 is: %s/n",buffer2);
	return buffer2;
}


/*****************************************************************************
*   Prototype    : BEEP_ctl
*   Description  : open and close alarm
*   Input        : int fd            
*                  unsigned int ctl  
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/21
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int BEEP_ctl(int fd,unsigned int ctl)
{
	switch(ctl)
    {
		case ALARM_CLOSE:ioctl(fd,0,2);break;
		case ALARM_OPEN:ioctl(fd,1,2);break;
		default:break;
	}
	return 0;
}


/*****************************************************************************
*   Prototype    : getAlarmFd
*   Description  : get the alarm fd
*   Input        : None
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/20
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int getAlarmFd()
{
    int fd;
    char *alarm_node = "/dev/buzzer_ctl";//蜂鸣器设备
    if( (fd = open(alarm_node,O_RDWR|O_NDELAY) )<0)
    {
		printf("APP open %s failed",alarm_node);
        return FAIL;
	}
    return fd;
}


/*****************************************************************************
*   Prototype    : getuartfd
*   Description  : get the uart fd
*   Input        : None
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/20
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int getuartfd()
{
    int fd;
    //uart1设备
    char *uart1 = "/dev/ttySAC3";
    if((fd = open(uart1, O_RDWR|O_NOCTTY) )<0)
    {
        printf("open %s is failed",uart1);
        return FAIL;
    }
    return fd;
}


