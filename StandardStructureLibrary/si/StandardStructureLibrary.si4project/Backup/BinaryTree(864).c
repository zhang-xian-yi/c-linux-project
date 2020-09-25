#include "./BinaryTree.h"


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
    //add node  the first   must be root node
    pBTree ret = (pBTree)Malloc(sizeof(BTree_t));

    ret->node_num = 0;
    ret->root = NULL;
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




