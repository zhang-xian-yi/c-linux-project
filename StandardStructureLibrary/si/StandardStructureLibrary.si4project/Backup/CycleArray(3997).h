/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : CycleArray.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/26
*  Last Modified :
*  Description   : CycleArray.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/26
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __CYCLEARRAY_H__
#define __CYCLEARRAY_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./base_types/nodes/wrap.h"
#include "./base_types/nodes/base/public.h"


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_CycleArray CycleArray_t;
typedef CycleArray_t*   pCycleArray;


/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern bool cycle_array_add(pCycleArray pCArray,const void* resource, uint32 i_elem_size );
extern pCycleArray cycle_array_create(uint32 elem_size,bool (* freefunc)(void * elem)  );
extern bool cycle_array_destory( pCycleArray pCarray );
extern bool cycle_array_empty( pCycleArray pCarray );
extern bool cycle_array_full( pCycleArray pCarray );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CYCLEARRAY_H__ */
