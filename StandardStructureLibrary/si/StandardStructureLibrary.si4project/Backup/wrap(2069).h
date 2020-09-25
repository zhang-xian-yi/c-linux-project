/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : wrap.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/2
*  Last Modified :
*  Description   : wrap.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/2
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __WRAP_H__
#define __WRAP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>



/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define DEBUG

//#define REALSE

#ifdef DEBUG
#define D_TRACE printf
#else
#define D_TRACE //
#endif

#ifdef REALSE
#define R_TRACE printf
#else
#define R_TRACE //
#endif



/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void* Malloc( unsigned int size );
extern void perror_usr_exit( const char* str );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __WRAP_H__ */
