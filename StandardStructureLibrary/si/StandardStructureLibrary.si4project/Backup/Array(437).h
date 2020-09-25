/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : Array.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/20
*  Last Modified :
*  Description   : Array.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/20
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __ARRAY_H__
#define __ARRAY_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <assert.h>
#include "./nodes/wrap.h"
#include "./nodes/base/public.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_ARRAY
{
    uint32 elem_num;
    uint32 elem_size;
    uint32 alloc_num;
    void*  elems;
    bool  (*freefn)(void* elem);
}Array_t;

typedef Array_t* pArray;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern pArray array_create( uint32 elem_size,bool (*freefunc)(void* elem) );
extern bool array_destory( pArray parray );
extern void*  array_get(pArray array, uint32 index );
extern bool array_grow( pArray parray );
extern bool array_set( pArray array, uint32 index, void* elem, uint32 elem_size );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ARRAY_H__ */
