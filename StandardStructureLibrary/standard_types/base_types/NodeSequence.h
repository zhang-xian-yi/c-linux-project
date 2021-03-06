/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : NodeSequence.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/6/5
*  Last Modified :
*  Description   : NodeSequence.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/6/5
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __NODESEQUENCE_H__
#define __NODESEQUENCE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./nodes/wrap.h"
#include "./nodes/base/public.h"
#include "./nodes/base/Node.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/

typedef struct _T_NodeSequence
{
    uint32 elem_num;
    uint32 elem_size;
    uint32 alloc_num;
    pNode*  elems;
    bool  (*freeNodefn)(pNode elem);
}NSequence_t;


typedef NSequence_t* pNSequence;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern bool nSequence_add( pNSequence pNSeq, pNode node );
extern bool nSequence_control( pNSequence pNSeq, bool (*operafn)(pNode one,uint32 nid), uint32 nid );
extern pNSequence nSequence_create( uint32 node_nums,uint32 node_size, bool(*freeNodefn)(pNode elem) );
extern bool nSequence_del( pNSequence pNSeq, uint32 nid );
extern bool nSequence_destory( pNSequence pNSeq );
extern pNode  nSequence_get( pNSequence pNSeq, uint32 nid );
extern bool nSequence_grow( pNSequence pNSeq );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __NODESEQUENCE_H__ */
