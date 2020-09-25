/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : SList.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/2
*  Last Modified :
*  Description   : SList.c header file
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
#ifndef __SLIST_H__
#define __SLIST_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./nodes/SListNode.h"



/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_LinkList
{
    pSListNode                phead;
    pSListNode                p_pos;
    uint32                    list_length;
}SList_t;

typedef SList_t*   pSList;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
//declare a func pointer and control the list
typedef bool (* slist_oper_pfun)(pSListNode temp,uint32 node_id);


/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern pSListNode getListNode(pSList plist , uint32 i_id );
extern bool slist_add( pSList plist, pSListNode node );
extern pSList slist_create( );
extern bool slist_delById( pSList plist, uint32 nid );
extern bool slist_destory( pSList plist );
extern bool slist_empty( pSList plist );
extern bool slist_control( pSList plist, slist_oper_pfun func_control,uint32 node_id);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SLIST_H__ */
