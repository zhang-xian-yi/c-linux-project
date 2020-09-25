#include "./BinaryTree.h"
#include "./Stack.h"

static pStack pstack = stack_create(8, sizeof(pBTNode), NULL);
/*
    Traversal does not require a delete operation 
    to be created without passing in a function that releases the node
*/
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
            //Mid-order deletes node data
            bTree_inRootTraverse(tree, freeBinaryTreeNode, 0);        
        }
    }
    //destory the file global stack
    stack_destory(pstack);
    pstack = NULL;
    memset(tree,0,sizeof(BTNode_t));
    free(tree);
    return TRUE;
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
                    //add inti tree
                    temp->lchild = i_nonde;
                    //set the parent node
                    temp->lchild->parent = temp;
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
                    //set the parent node
                    temp->rchild->parent = temp;
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
*                  pBTNode node
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
bool bTree_del( pBTree tree, pBTNode treeNode )
{
    bool ret = FALSE;
    if(NULL == treeNode->lchild && NULL == treeNode->rchild )
    {
        //Release leaf node
        //ret = freeNode(treeNode->node);
    }
    else if(NULL != treeNode->lchild && NULL == treeNode->rchild)
    {
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
    }
    else if(NULL == treeNode->lchild && NULL != treeNode->rchild)
    {
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
    }
    //free the pBTnode space
    ret = freeBinaryTreeNode(treeNode);
    return ret;
}


/*****************************************************************************
*   Prototype    : bTree_preRootTraverse
*   Description  : Non-recursive Traversal first order algorithm of binary
                   sort tree
*   Input        : pBTree tree
*                  bool (*funcon)(pBTNode node,uint32 nod)
*                  uint32 nid
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/22
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void bTree_preRootTraverse( pBTree tree, bool (*funcon)(pBTNode node,uint32 nid), uint32 nid )
{
    pBTNode temp = tree->root;
    //static pStack pstack clear;
    stack_clear(pstack);
    if(NULL != temp)
	{
		stack_push(pstack, (void*)temp);
		while(FALSE == stack_empty(pstack))
		{
			temp = (pBTNode)stack_pop(pstack);
			funcon(temp,nid);
			while(NULL != temp)
			{
				if(NULL != temp->lchild)
				{
					funcon(temp,nid);
				}
				
				if(NULL != temp->rchild )
				{
					stack_push(pstack,temp->rchild);
				}
				temp = temp->lchild;
			}
		}
	}    
}

/*****************************************************************************
*   Prototype    : bTree_inRootTraverse
*   Description  : The middle order non-recursive traversal algorithm of
                   binary sort tree
*   Input        : None
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/22
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void bTree_inRootTraverse(pBTree tree, bool (*funcon)(pBTNode node,uint32 nid), uint32 nid)
{
	pBTNode temp = tree->root;
    
	if(NULL != temp)
	{
        //clear the stack prevent left data
		stack_clear(pstack);
		stack_push(pstack,(void*)temp);
		
		while( FALSE == stack_empty(pstack))
		{
			//push ledt child
    		while(NULL != stack_peek(pstack) )
    		{
                pBTNode t_node = (pBTNode)stack_peek()-;
    			stack_push(pstack,t_node->lchild);
    		}
    		//If the root node is empty, unstack;
    		stack_pop();
    		if(FALSE == stack_empty(pstack))
    		{
    		    pBTNode t = (pBTNode)stack_pop(pstack);
    		    funcon(t,nid);
    		    stack_push(pstack,t->rchild);
    		}
		}
	}
}


/*****************************************************************************
*   Prototype    : bTree_postRootTraverse
*   Description  : post-traversal non-recursive algorithm
*   Input        : pBTree tree                  
*                  bool (*funcon)(pBTNode node  
*                  uint32 nid)                  
*                  uint32 nid                   
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/22
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void  bTree_postRootTraverse(pBTree tree, bool (*funcon)(pBTNode node,uint32 nid), uint32 nid)
{
	pBTNode temp = tree->root;
	if(NULL != temp)
	{
		
		stack_push(pstack,(void*)temp);

        bool flag;
		pBTNode p = NULL;
		
		while(FALSE == stack_empty(pstack))
		{
			//push ledt child
    		while(NULL != stack_peek(pstack) )
    		{
                pBTNode t_node = (pBTNode)stack_peek()-;
    			stack_push(pstack,t_node->lchild);
    		}
			stack_pop();
			
			while(FALSE ==  stack_empty(pstack))
			{
				temp = stack_peek();
				
				if(NULL == temp->rchild  || temp.rchild == p)
				{
					funcon(temp,nid);
					stack_pop();
					p = temp;
					flag = true;
				}
				else
				{
					stack_push(pstack,temp->rchild);
					flag = false;
				}
				
				if(FALSE ==  flag)
				{
					break;
				}
			}
		}
	}
}




