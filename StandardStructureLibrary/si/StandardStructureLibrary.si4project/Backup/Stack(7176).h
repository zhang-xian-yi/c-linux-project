/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : Stack.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/13
*  Last Modified :
*  Description   : Stack.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/13
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __STACK_H__
#define __STACK_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <assert.h>
    
#include "./base_types/nodes/wrap.h"
#include "./base_types/nodes/base/public.h"
#include "./base_types/nodes/base/Node.h"




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct 
{
    uint32      elem_num;      //stack elem num
    uint32      alloc_length;    //alloc the memery 
    uint32      elem_size;       //elem size
    pNode *     elems;          //stack space
    bool    (* freefn)(pNode node); // free the memery func pointer
} Stack_t;

typedef Stack_t*   pStack;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void stack_destory(pStack  pstack);
extern void stack_grow(pStack pstack);
extern void stack_create(uint32 elem_num,uint32 elemsize, void (* freefn)(void *));
extern void stack_pop(pStack pstack,pNode  elemaddr);
extern void stack_push(pStack pstack,pNode  elemaddr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __STACK_H__ */
