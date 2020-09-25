#include "./SListNode.h"

/*****************************************************************************
*   Prototype    : compare2
*   Description  : compare two list node 
*   Input        : pSListNode one
*                  pSListNode two
*   Output       : big or small equal
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/2
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int compare2( pSListNode one, pSListNode two )
{
    //return bigger mean one id > two id
    return compare2Node(one->pdata, two->pdata);
}

/*****************************************************************************
*   Prototype    : setListNode
*   Description  : set the pdata and assign it
*   Input        : pSListNode p_l_node
*                  pNode data
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/2
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void setListNode(pSListNode p_l_node, pNode data)
{
    setNode(p_l_node->pdata, data->id, data->count, data->pnode);
    p_l_node->pnext = NULL;
}



/*****************************************************************************
*   Prototype    : emptyListNode
*   Description  : if the list node is null or listnode->data is null return
                   null
*   Input        : pSListNode p_l_node
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/2
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool emptyListNode( pSListNode p_l_node )
{
    //input null node 
    if(NULL == p_l_node )
    {
        return TRUE;
    }
    //confirm the pdata is not null    
    return isEmptyNode(p_l_node->pdata);
}

/*****************************************************************************
*   Prototype    : freeListNode
*   Description  : free a list node
*   Input        : pSListNode list_node
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/2
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void freeListNode( pSListNode list_node )
{
    freeNode(list_node->pdata);
    list_node->pdata = NULL;
    list_node->pnext = NULL;
    //free the list node memery
    free(list_node);
    D_TRACE("free a slist node at %p and size %d \n",list_node,sizeof(SListNode_t));
}

/*****************************************************************************
*   Prototype    : equal2listnodes
*   Description  : confirm the two list node is equal
*   Input        : pSListNode one
*                  pSListNode two
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/2
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool equal2ListNodes( pSListNode one, pSListNode two )
{
    if(one->pdata->id  == two->pdata->id)
    {
        return TRUE;
    }
    return FALSE;
}


/*****************************************************************************
*   Prototype    : getListNodeMem
*   Description  : get the a list node memery
*   Input        : pNode data
*   Output       : None
*   Return Value : pSListNode
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/4
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pSListNode getListNodeMem( pNode data )
{
    pSListNode temp = (pSListNode)Malloc(sizeof(SListNode_t));
    temp->pdata =data;
    temp->pnext = NULL;
}

