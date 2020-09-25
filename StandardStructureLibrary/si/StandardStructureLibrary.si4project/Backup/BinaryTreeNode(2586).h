/******************************************************************************
*
*  Copyright (C), 2015-2025, mengxing Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : BinaryTreeNode.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : BinaryTreeNode.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/6/10
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __BINARYTREENODE_H__
#define __BINARYTREENODE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./base/Node.h"



/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_BinaryTreeNode
{
    pNode                           node;
    struct _T_BinaryTreeNode *      lchild;
    struct _T_BinaryTreeNode *      rchild;
}BTNode_t;

typedef BTNode_t* pBTNode;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern int compare2TreeNode( pBTNode one, pBTNode two );
extern bool freeBinaryTreeNode(pBTNode treeNode);
extern pBTNode getBinaryTreeNodeMem( uint32 nid, uint32 node_size, void* pnode );
extern bool isEmptyTreeNode( pBTNode pnode );
extern bool isEqual2TreeNode( pBTNode one, pBTNode two );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __BINARYTREENODE_H__ */
