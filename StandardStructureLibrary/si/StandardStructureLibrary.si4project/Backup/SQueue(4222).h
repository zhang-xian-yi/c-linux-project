/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : SQueue.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/10
*  Last Modified :
*  Description   : SQueue.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/10
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __SQUEUE_H__
#define __SQUEUE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./base_types/SList.h"
#include "./base_types/nodes/wrap.h"




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef SListNode_t     QueueNode_t;
typedef pSListNode      pQueueNode;

typedef struct _T_SQUEUE
{
    SList_t         queue;
    pQueueNode      pfrist;
    pQueueNode      plast;
}SQueue_t;

typedef SQueue_t *   pQueue;

typedef bool (*queue_oper_func)(pQueueNode temp,uint32 n_id);
/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern bool squeue_add( pQueue pqueue, pQueueNode node);
extern bool squeue_control( pQueue pqueue ,queue_oper_func func_control,uint32 n_id);
extern pQueue squeue_create(  );
extern bool squeue_destory( pQueue queue );
extern pQueueNode squeue_pop(pQueue pqueue );
extern pQueueNode getQueueNodeMem( uint32 id, uint32 count, void* args );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SQUEUE_H__ */
