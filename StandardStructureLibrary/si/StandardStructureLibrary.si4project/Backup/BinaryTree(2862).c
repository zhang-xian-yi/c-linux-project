#include "./nodes/BinaryTreeNode.h"

typedef struct _T_Binary_Tree
{
    uint32   node_num;
    pBTNode  root;
}BTree_t;

typedef BTree_t*  pBTree;

#define ROOT_ID         50

/*****************************************************************************
*   Prototype    : bTree_create
*   Description  : get the tree mem create a tree
*   Input        : None
*   Output       : None
*   Return Value : pBTree
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/12
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pBTree bTree_create()
{
    pBTree ret = (pBTree)Malloc(sizeof(BTree_t));
    pBTNode node = getBinaryTreeNodeMem(ROOT_ID, 0, NULL);

    ret->node_num = 1;
    ret->root = node;
    return ret;
}

/*****************************************************************************
*   Prototype    : bTree_destory
*   Description  : destory a binary tree
*   Input        : pBTree tree
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/14
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool bTree_destory( pBTree tree )
{
    if(NULL != tree)
    {
        if(NULL != tree->root)
        {
            freeBinaryTreeNode(tree->root->lchild);
            freeBinaryTreeNode(tree->root->rchild);
            freeBinaryTreeNode(tree->root);
            return TRUE;
        }
    }
    return FALSE;
}

/*****************************************************************************
*   Prototype    : bTree_control
*   Description  : control some nodes  and operated it
*   Input        : pBTree tree
*                  bool (*operafun)(pBTreeNode node,uint32 nid)
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/14
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool bTree_control( pBTree tree, bool (*operafun)(pBTNode node,uint32 nid),uint32 nid )
{
    if(NULL != tree)
    {
        if(NULL != tree->root)
        {
            freeBinaryTreeNode(tree->root->lchild);
            if(nid == tree->root->node->id)
            {
                operafun(tree->root,nid);
                return TRUE;
            }
            freeBinaryTreeNode(tree->root->rchild);
        }
    }
    return FALSE;
}



