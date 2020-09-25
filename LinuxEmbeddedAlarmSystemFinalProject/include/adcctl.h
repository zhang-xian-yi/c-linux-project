/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : adcctl.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2019/12/19
*  Last Modified :
*  Description   : adcctl.c header file
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
#ifndef __ADCCTL_H__
#define __ADCCTL_H__


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


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern int getADCfd(  );
extern int getADCValue( int fd );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ADCCTL_H__ */
