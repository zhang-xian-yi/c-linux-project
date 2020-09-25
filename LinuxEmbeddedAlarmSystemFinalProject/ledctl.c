#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "ledctl.h"

/*****************************************************************************
*   Prototype    : led2_shine
*   Description  : shine the led2
*   Input        : int fd
*   Output       : None
*   Return Value : void
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
void led2_shine( int fd )
{
    ioctl(fd,SHINE_LED,1);
}

/*****************************************************************************
*   Prototype    : led2_off
*   Description  : off the led 2
*   Input        : int fd
*   Output       : None
*   Return Value : void
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
void led2_off( int fd )
{
    ioctl(fd,OFF_LED,1);
}



/*****************************************************************************
*   Prototype    : led3_shine
*   Description  : shine the led
*   Input        : int fd
*   Output       : None
*   Return Value : void
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
void led3_shine( int fd )
{
    ioctl(fd,SHINE_LED,2);
}

/*****************************************************************************
*   Prototype    : led3_off
*   Description  : off the led 3
*   Input        : int fd
*   Output       : None
*   Return Value : void
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
void led3_off( int fd )
{
    ioctl(fd,OFF_LED,2);
}

/*****************************************************************************
*   Prototype    : getLedCtlFd
*   Description  : get the zxy ctl led
*   Input        : None
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
int getLedCtlFd(  )
{
    char *zxy_ctl_node = "/dev/zxy_led_ctl";
    int fd = 0;
    if((fd = open(zxy_ctl_node,O_RDWR|O_NDELAY))<=0)
    {
		printf("APP open %s failed",zxy_ctl_node);
	}
    return fd;
}


/*****************************************************************************
*   Prototype    : cycleShineLed
*   Description  : cycle flashing the led2 and led 3
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
void cycleShineLed( int fd )
{
    sleep(1);
    ioctl(fd,SHINE_LED,1);
	ioctl(fd,OFF_LED,2);
	sleep(1);
	ioctl(fd,OFF_LED,1);
	ioctl(fd,SHINE_LED,2);
    sleep(1);
}

