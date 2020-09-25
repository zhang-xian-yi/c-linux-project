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


/*****************************************************************************
*   Prototype    : bTree_add
*   Description  : add a btreenode  into input pBtree
*   Input        : pBTree ptree
*                  pBTNode i_nonde
*   Output       : None
*   Return Value : 
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/21
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool  bTree_add( pBTree ptree,pBTNode i_nonde )
{
    if(NULL == ptree->root)
    {
        //tree is empty
        ptree->root = i_nonde;
    }
    else
    {
        //insert node by id bigger or small  orderly
        pBTNode temp = ptree->root;
        while(TRUE)
        {
            //Put the smaller value on the left
            if(i_nonde->node->id < temp->node->id)
            {
                if(NULL == temp->lchild)
                {
                    temp->lchild = i_nonde;
                }
                //temp->lchild is not null go into its lchild
                temp = temp->lchild;
            }
            else if(i_nonde->node->id > temp->node->id)
            {
                //Put the bigger value on the right
                if(NULL == temp->rchild)
                {
                    temp->rchild = i_nonde;
                }
                //temp->rchild is not null go into its rchild
                temp = temp->rchild;
            }
            else if(i_nonde->node->id == temp->node->id)
            {
                //replace the node value
                if(NULL == i_nonde->node && NULL == i_nonde->rchild)
                {
                    //Free up the original node space
                    freeNode(temp->node);
                    //Replace the node's data
                    temp->node = i_nonde->node;
                }
                    
                
            }
        }
    }
}



/*****************************************************************************
*   Prototype    : bTree_del
*   Description  : delete a bTreeNode from the input ptree
*   Input        : pBTree tree
*                  uint32 id
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/21
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool bTree_del( pBTree tree, uint32 id )
{
    
}

