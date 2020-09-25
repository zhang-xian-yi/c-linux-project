/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : DCycleList.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/16
*  Last Modified :
*  Description   : DCycleList.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/16
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __DCYCLELIST_H__
#define __DCYCLELIST_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./base_types/nodes/base/Node.h"
#include "./base_types/nodes/DListNode.h"
#include "./base_types/nodes/wrap.h"
#include "./base_types/nodes/base/public.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef pDListNode    pCycleListNode;
typedef DListNode_t   CycleListNode_t;

typedef bool (*cycle_list_func_oper)(pCycleListNode temp,uint32 nid);

typedef struct _T_DCycleList
{
    uint32              list_length;
    pCycleListNode      phead;
    pCycleListNode      ptail;
}DCycleList_t;

typedef DCycleList_t* pCycleList;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern bool cycle_list_add( pCycleList plist, uint32 list_length,pCycleListNode node );
extern bool cycle_list_control( pCycleList plist, cycle_list_func_oper func ,uint32 nid);
extern pCycleList cycle_list_create( void );
extern bool cycle_list_del( pCycleList plist, pCycleListNode del_node );
extern bool cycle_list_destory( pCycleList  plist);
extern bool cycle_list_empty( pCycleList plist );
extern bool cycle_list_full( pCycleList plist,uint32 list_length );
extern bool equal2CycleListNode( pCycleListNode one, pCycleListNode two );
extern pCycleListNode getCycleListNodeMem( uint32 id, uint32 size, pNode node );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DCYCLELIST_H__ */
