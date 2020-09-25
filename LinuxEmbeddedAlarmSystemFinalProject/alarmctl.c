#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/ioctl.h>
/*���Ӵ��ڲ������ͷ�ļ�*/
#include <termios.h>

#include "alarmctl.h"

#define __NO_VERSION__

/*���ô��ڲ����������ʡ�����λ��У��λ��ֹͣλ*/
int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio, oldtio;						//�¾�termios�ṹ�����
	if(tcgetattr(fd, &oldtio) != 0)						//��ȡ��ǰ����
	{
		perror("SetupSerial 1");
		return -1;
	}
	
	//�µĽṹ���������--���Ƕ�һ���½ṹ�����ʼ��
	bzero(&newtio, sizeof(newtio));						//���½ṹ������
	newtio.c_cflag |= CLOCAL | CREAD;					//ͨ��ͬʱʹ�ܣ�ȷ�����򲻱������˿ڿ��ƺ��źŸ��ţ�ͬʱ������������ȡ��������ݡ�
	newtio.c_cflag &= ~CSIZE;							//����λ��0
	
	switch(nBits)				//��������λ--����λ�Լ�����
	{
		case 7:
			newtio.c_cflag |= CS7;						//��λ
			break;
		case 8:
			newtio.c_cflag |= CS8;						//��λ
			break;
	}
	
	switch(nEvent)				//������żУ��
	{
		case 'O'://��У��
			newtio.c_cflag |= PARENB;					//����У��λ
			newtio.c_cflag |= PARODD;					//ʹ����У��(����ñ�־��ʾʹ��żУ��)
			newtio.c_iflag |= (INPCK | ISTRIP);			//���ü��� + ��ȥ�ڰ�λ
			break;
		case 'E'://żУ��
			newtio.c_cflag |= PARENB;					//����У��λ
			newtio.c_cflag &= ~PARODD;					//ʹ��żУ��(����ñ�־��ʾʹ��żУ��)
			newtio.c_iflag |= (INPCK | ISTRIP);			//���ü��� + ��ȥ�ڰ�λ
			break;
		case 'N'://��У��
			newtio.c_cflag &= ~PARENB;					//��У��
			break;
	}
	
	switch(nSpeed)				//���ô����ٶ�
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
	
	if(nStop == 1)				//����ֹͣλ
	{
		newtio.c_cflag &= ~CSTOPB;						//һλֹͣλ
	}
	else if(nStop == 2)
	{
		newtio.c_cflag |= CSTOPB;						//��λֹͣλ
	}
	//���VTIME=0��VMIN=0�������ܷ��ȡ�����ݣ�read������������
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd, TCIFLUSH);								//����������ڷ�����I/O ����
	//������Ч
	if((tcsetattr(fd, TCSANOW, &newtio)) != 0)			//�������ݴ�����Ͼ������ı�����
	{
		perror("com set error");
		return -1;
	}
	
	return 0;
}


/*����д����*/
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
int write_UART1(int fd,char *write1,int i)//fd:�豸��write1��д������;i:д���ݴ���
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

/*���ڶ�����*/
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
	/*������ڶ�������,��ʼ���մ����յ�������*/
	while((nByte = read(fd, buffer, 512))>0)
	{
		buffer[nByte+1] = '\0';//�����ݺ�ӽ�����
	}
    memcpy(buffer1,buffer,strlen(buffer));//����һ��ֵ
	write(fd,buffer,strlen(buffer));//�ѽ��յ��ķ��ͻ�ȥ
	write(fd,buffer1,strlen(buffer1));//�ѽ��յ��ķ��ͻ�ȥ
	memset(buffer, 0, strlen(buffer));//������buffer���
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
    char *alarm_node = "/dev/buzzer_ctl";//�������豸
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
    //uart1�豸
    char *uart1 = "/dev/ttySAC3";
    if((fd = open(uart1, O_RDWR|O_NOCTTY) )<0)
    {
        printf("open %s is failed",uart1);
        return FAIL;
    }
    return fd;
}


