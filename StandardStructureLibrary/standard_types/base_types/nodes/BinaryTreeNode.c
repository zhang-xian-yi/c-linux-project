#include "./BinaryTreeNode.h"



/*****************************************************************************
*   Prototype    : getBinaryTreeNodeMem
*   Description  : get a memery of binary tree node
*   Input        : uint32 nid
*                  uint32 node_size
*                  void* pnode
*   Output       : None
*   Return Value : pBTNode
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/7
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pBTNode getBinaryTreeNodeMem( uint32 nid, uint32 node_size, void* pnode )
{
    pNode temp = getNodeMem(nid, node_size, pnode);
    pBTNode ret = (pBTNode)Malloc(sizeof(BTNode_t));
    ret->node = temp;
    ret->lchild = NULL;
    ret->rchild = NULL;
    ret->parent = NULL;
    return ret;
}


/*****************************************************************************
*   Prototype    : freeBinaryTreeNode(pBTNode treeNode)
*   Description  : free the memery of binary  Tree node
*   Input        : pBTNode treeNode
*                  uint32 nid    //unuser parag
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/7
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool freeBinaryTreeNode(pBTNode treeNode£¬uint32 nid)
{
    bool ret = FALSE;
    ret = freeNode(treeNode->node);
    memset(treeNode,0,sizeof(BTNode_t));
    free(treeNode);
    return 0;
}


/*****************************************************************************
*   Prototype    : compare2TreeNode
*   Description  : compare 2 binary node is equal
*   Input        : pBTNode one
*                  pBTNode two
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/7
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int compare2TreeNode( pBTNode one, pBTNode two )
{
    return  compare2Node(one->node, two->node);
}

/*****************************************************************************
*   Prototype    : isEqual2TreeNode
*   Description  : confirm the two tree node is equal
*   Input        : pBTNode one
*                  pBTNode two
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/8
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool isEqual2TreeNode( pBTNode one, pBTNode two )
{
    return EQUAL == compare2Node(one, two);
}

/*****************************************************************************
*   Prototype    : isEmptyTreeNode
*   Description  : confirm the tree node is empty or not
*   Input        : pBTNode node
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/10
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool isEmptyTreeNode( pBTNode pnode )
{
    return isEmptyNode(pnode->node);
}


