/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : utils.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2019/11/16
*  Last Modified :
*  Description   : utils.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2019/11/16
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __UTILS_H__
#define __UTILS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define DEBUG

#ifdef DEBUG
#define TRACE printf
#else
#define TRACE //
#endif

#define size_t unsigned int
#define bool char
#define true   1
#define false  0


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void* Malloc( size_t size );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UTILS_H__ */
