/******************************************************************************
*
*  Copyright (C), 2015-2025, mengxing Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : BinaryTree.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/6/22
*  Last Modified :
*  Description   : BinaryTree.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/6/22
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./nodes/BinaryTreeNode.h"



/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_BinaryTree
{
    uint32  node_num;
    pBTNode root;
}BTree_t;

typedef BTree_t *  pBTree;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern bool  bTree_add( pBTree ptree,pBTNode i_nonde );
extern pBTree bTree_create();
extern bool bTree_del( pBTree tree, pBTNode node );
extern bool bTree_destory( pBTree tree );
extern void bTree_inRootTraverse(pBTree tree, bool (*funcon)(pBTNode node,uint32 nid), uint32 nid);
extern void  bTree_postRootTraverse(pBTree tree, bool (*funcon)(pBTNode node,uint32 nid), uint32 nid);
extern void bTree_preRootTraverse( pBTree tree, bool (*funcon)(pBTNode node,uint32 nid), uint32 nid );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __BINARYTREE_H__ */
