/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : SListNode.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/2
*  Last Modified :
*  Description   : SListNode.c header file
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
#ifndef __SLISTNODE_H__
#define __SLISTNODE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./base/Node.h"
#include "./wrap.h"


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_LinkListNode
{
    pNode               pnext;
    pNode               pdata;
}SListNode_t;

typedef SListNode_t*   pSListNode;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern int compare2( pSListNode one, pSListNode two );
extern bool emptyListNode( pSListNode p_l_node );
extern void setListNode(pSListNode p_l_node, pNode data);
extern bool equal2ListNodes( pSListNode one, pSListNode two );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SLISTNODE_H__ */
