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




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern static pQueueNode deepCopyQueueNode( pQueueNode one );
extern bool squeue_add( pQueue pqueue, pQueueNode node);
extern bool squeue_control( pQueue pqueue ,queue_oper_func func_control,uint32 n_id);
extern pQueue squeue_create(  );
extern bool squeue_destory( pQueue queue );
extern pQueueNode squeue_pop(pQueue pqueue );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SQUEUE_H__ */
