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
    if(NULL == treeNode->lchild && NULL == treeNode->rchild )
    {
        //Release leaf node
        freeNode(treeNode->node);
    }
    else if(NULL != treeNode->lchild && NULL == treeNode->rchild)
    {
        //left child is not null
        freeNode(treeNode->node);
        //Make sure it's left or right
        if(treeNode->node->id < treeNode->parent->node->id)
        {
            //del node is parents left child
            treeNode->parent->lchild = treeNode->lchild;
        }
        else if(treeNode->node->id > treeNode->parent->node->id)
        {
            //del node is parents right child
            treeNode->parent->rchild = treeNode->lchild;
        }
        mmeset(treeNode,0,sizeof(BTNode_t));
        free(treeNode);
    }
    else if(NULL == treeNode->lchild && NULL != treeNode->rchild)
    {
        //right child is not null
        freeNode(treeNode->node);
        //Make sure it's left or right
        if(treeNode->node->id < treeNode->parent->node->id)
        {
            //del node is parents left child
            treeNode->parent->lchild = treeNode->rchild;
        }
        else if(treeNode->node->id > treeNode->parent->node->id)
        {
            //del node is parents right child
            treeNode->parent->rchild = treeNode->rchild;
        }
        mmeset(treeNode,0,sizeof(BTNode_t));
        free(treeNode);
    }
    else if(NULL != treeNode->lchild && NULL != treeNode->rchild)
    {
        //Find the largest node in the left subtree
        pBTNode temp = treeNode->lchild;
        while(TRUE)
        {
            if(NULL == temp->rchild  && NULL == temp->lchild )
            {
                //must is leaf node
                break;
            }
            temp = temp->rchild;
            
        }
        //finnded replace node
        temp->parent->rchild = NULL;
        // Replaces the location of the node to be deleted
        temp->parent = treeNode->parent;
        
        //Make sure it's left or right
        if(treeNode->node->id < treeNode->parent->node->id)
        {
            //replace
            treeNode->parent->lchild = temp;
            temp->lchild = treeNode->lchild;
        }
        else if(treeNode->node->id > treeNode->parent->node->id)
        {
            //del node is parents right child
            treeNode->parent->rchild = temp;
            temp->rchild = treeNode->rchild;
        }
        //realse del node
        freeNode(treeNode->node);
    }
    //free the pBTnode space    
    memset(treeNode,0,sizeof(BTNode_t));
    free(treeNode);
    
    return ret;
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


