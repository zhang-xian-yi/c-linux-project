#include "adcctl.h"

#include<linux/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>


/*****************************************************************************
*   Prototype    : getADCValue
*   Description  : int
*   Input        : int fd
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/19
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int getADCValue( int fd )
{
    int adc;
    int value = -1;
    while(1)
    {
		adc = read(fd);
        value = (10000.0*adc)/4096;
        printf("value is %0.2f koxxxxxx\n",value);//输出电阻
        if(value > 0)
        {
            return value;
        }
        //轮询获取 adc 的值
        sleep(1);
    }
}


/*****************************************************************************
*   Prototype    : getADCfd
*   Description  : get the adc the fd
*   Input        : int
*   Output       : None
*   Return Value : 
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/19
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int getADCfd(  )
{
    int fd;
	char *adc_node = "/dev/zxy_adc_ctl";
    fd = open(adc_node,O_RDWR|O_NDELAY);
    if(fd<0)
    {
        printf("open fail\n");
        return 0;
    }
    return fd;
}

