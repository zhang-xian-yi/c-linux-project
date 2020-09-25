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




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void stack_destory(pStack  pstack);
extern void stack_grow(pStack pstack);
extern void stack_new(pStack  s,int elemsize, void (* freefn)(void *));
extern void stack_pop(pStack pstack,void * elemaddr);
extern void stack_push(pStack pstack,void * elemaddr);
extern static void string_free(void * elem);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __STACK_H__ */
