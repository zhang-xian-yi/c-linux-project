/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : public.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/1
*  Last Modified :
*  Description   : public.h header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/1
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __PUBLIC_H__
#define __PUBLIC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      typedef define all type                 *
 *----------------------------------------------*/
typedef unsigned char       bool;
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long       uint64;



/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define TRUE        1
#define FALSE       0

#define EQUAL       -1
#define BIGGER      -125
#define SMALLER     125


#define MAX_INT8    0x7f
#define MIN_INT8    0xff
#define MAX_INT16   0x7fff
#define MIN_INT16   0xffff

#define MAX_INT32   0x7fffffff
#define MIN_INT32   0xffffffff
#define MAX_INT64   0x7fffffffffffffff
#define MIN_INT64   0xffffffffffffffff

#define MAX_UNSIGNED_INT8    0xff
#define MIN_UNSIGNED_INT8    0
#define MAX_UNSIGNED_INT16   0xffff
#define MIN_UNSIGNED_INT16   0

#define MAX_UNSIGNED_INT32   0xffffffff
#define MIN_UNSIGNED_INT32   0
#define MAX_UNSIGNED_INT64   0xffffffffffffffff
#define MIN_UNSIGNED_INT64   0

#define NULL                 0x0

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PUBLIC_H__ */
