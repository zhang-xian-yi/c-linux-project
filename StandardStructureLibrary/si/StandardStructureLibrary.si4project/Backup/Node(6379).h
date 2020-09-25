/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : Node.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/1
*  Last Modified :
*  Description   : Node.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/1
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __NODE_H__
#define __NODE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./public.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_Node
{
    uint32  id;
    /* BEGIN: Added for PN:1 by zhangxianyi, 2020/5/16 */
    uint32  size;
    /* END:   Added for PN:1 by zhangxianyi, 2020/5/16 */
    void*   pnode;
}Node_t;

typedef Node_t* pNode; 

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/


/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern int compare2Node( pNode one, pNode two );
extern bool equals2Node( pNode one, pNode two );
extern bool isEmptyNode( pNode node );
extern void freeNode( pNode node );

/* BEGIN: Modified for PN:1 by zhangxianyi, 2020/5/16 */

extern pNode getNodeMem( uint32 i_id, uint32 i_size, void* args );
extern void setNode(pNode p_node, uint32 id, uint32 i_size, void* node );

/* END:   Modified for PN:1 by zhangxianyi, 2020/5/16 */

extern pNode deepCopyNode(pNode i_node,uint32 i_pNode_data_size);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __NODE_H__ */
