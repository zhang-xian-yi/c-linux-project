/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : FixArray.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/26
*  Last Modified :
*  Description   : FixArray.c header file
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
#ifndef __FixARRAY_H__
#define __FixARRAY_H__


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
#include "./base_types/nodes/base/Node.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_FixArray FixArray_t;

typedef FixArray_t*   pFixArray;


/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern bool fix_array_add(pFixArray pFArray,const void* resource, uint32 i_elem_size );
extern pFixArray fix_array_create(uint32 length,uint32 elem_size,bool (* freefunc)(void * elem)  );
extern bool fix_array_destory( pFixArray pFArray );
extern bool fix_array_empty( pFixArray pFArray );
extern bool fix_array_full( pFixArray pFArray );
extern pNode fix_array_get(pFixArray pFArray,uint32 nid);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CYCLEARRAY_H__ */
