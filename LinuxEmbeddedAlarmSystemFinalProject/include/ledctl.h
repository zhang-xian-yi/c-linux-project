/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : ledctl.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2019/12/19
*  Last Modified :
*  Description   : ledctl.c header file
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
#ifndef __LEDCTL_H__
#define __LEDCTL_H__


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
#define SHINE_LED 1
#define OFF_LED 0

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void cycleShineLed( int fd );
extern int getLedCtlFd(  );
extern void led2_off( int fd );
extern void led2_shine( int fd );
extern void led3_off( int fd );
extern void led3_shine( int fd );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LEDCTL_H__ */
