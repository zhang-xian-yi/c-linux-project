#include "./base/Node.h"



typedef struct _T_BinaryTreeNode
{
    pNode                           node;
    struct _T_BinaryTreeNode *      lchild;
    struct _T_BinaryTreeNode *      rchild;
}BTNode_t;

typedef BTNode_t* pBTNode;


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
    return ret;
}


/*****************************************************************************
*   Prototype    : freeBinaryTreeNode(pBTNode treeNode)
*   Description  : free the memery of binary  Tree node
*   Input        : pBTNode treeNode
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
bool freeBinaryTreeNode(pBTNode treeNode)
{
    bool ret = freeNode(treeNode);
    memset(treeNode,0,sizeof(BTNode_t));
    return ret;
}


/*****************************************************************************
*   Prototype    : compare2TreeNode
*   Description  : compare 2 binary node is equal
*   Input        : pBTNode one
*                  pBTNode two
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
bool compare2TreeNode( pBTNode one, pBTNode two )
{
    return EQUAL == compare2Node(one->node, two->node);
}




