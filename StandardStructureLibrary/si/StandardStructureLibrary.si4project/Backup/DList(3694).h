/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : DList.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/9
*  Last Modified :
*  Description   : DList.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/9
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __DLIST_H__
#define __DLIST_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./nodes/DListNode.h"
#include "./nodes/wrap.h"


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_DLinkList
{
    pDListNode                phead;   //a node  without pdata 
    pDListNode                p_pos;   //a node with the last list node
    uint32                    list_length;
}DList_t;

typedef DList_t*   pDList;
//declare a func pointer and control the list
typedef bool (* dlist_oper_pfun)(pDListNode temp,uint32 node_id);


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern bool dlist_add( pDList pdlist, pDListNode node );
extern bool dlist_control( pDList pdlist,dlist_oper_pfun func_control,uint32 node_id );
extern pDList  dlist_create(  );
extern bool dlist_del( pDList pdlist, pDListNode del_node );
extern void dlist_destory( pDList pdlist );
extern bool dlist_empty( pDList pdlist );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DLIST_H__ */
