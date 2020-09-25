/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : AlarmSystem.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2019/12/19
*  Last Modified :
*  Description   : AlarmSystem.c header file
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
#ifndef __ALARMSYSTEM_H__
#define __ALARMSYSTEM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "utils.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define SUCCESS 1
#define FAILED -1



/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
enum AlarmSystem_status 
{
    ALARM_SYSTEM_COLSE = 0,
    ALARM_SYSTEM_NORMAL =1,
    ALARM_SYSTEM_EXCEPTION=2
};

typedef struct _T_Alarm
{
    //alarm file desc
    int led_fd;
    int vol_fd;
    int alarm_fd;
    //urat fd
    int uart_fd;
    enum AlarmSystem_status status;
    //adc fd
    int adc_fd;
}alarm_t,*palarm;

/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern int alarm_system_destory( palarm temp );
extern int alarm_system_init( palarm temp);
extern int alarm_system_open(palarm temp);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ALARMSYSTEM_H__ */
