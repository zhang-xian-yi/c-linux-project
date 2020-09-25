/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : zxy_alarm.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2019/12/19
*  Last Modified :
*  Description   : zxy_alarm.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2019/12/19
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __ZXY_ALARM_H__
#define __ZXY_ALARM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define ALARM_OPEN 1
#define ALARM_CLOSE 0

#define SUCC 0
#define FAIL -1

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/


/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern int BEEP_ctl(int fd,unsigned int ctl);
extern char * read_UART1(int fd);
extern int write_UART1(int fd,char *write1,int i);
extern int getAlarmFd();
extern int getuartfd();


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ZXY_ALARM_H__ */
