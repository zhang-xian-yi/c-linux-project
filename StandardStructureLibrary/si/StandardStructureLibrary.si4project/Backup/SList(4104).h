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
#include "./nodes/include/wrap.h"




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_LinkList
{
    pListNode                phead;
    pListNode                p_pos;
    uint32                   list_length;
}SList_t;

typedef SList_t*   pSList;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern pListNode getListNode(pSList plist , uint32 i_id );
extern bool slist_add( pSList plist, pListNode node );
extern pSList slist_create( int length );
extern bool slist_del(pSList plist, pListNode temp );
extern void slist_destory( pSList plist );
extern bool slist_empty( pSList plist );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SLIST_H__ */
