#include "./include/SListNode.h"

/*****************************************************************************
*   Prototype    : compare2
*   Description  : compare two list node 
*   Input        : pListNode one
*                  pListNode two
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
int compare2( pListNode one, pListNode two )
{
    //return bigger mean one id > two id
    return compare2Node(one->pdata, two->pdata);
}

/*****************************************************************************
*   Prototype    : setListNode
*   Description  : set the pdata and assign it
*   Input        : pListNode p_l_node
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
void setListNode(pListNode p_l_node, pNode data)
{
    setNode(p_l_node->pdata, data->id, data->count, data->pnode);
    p_l_node->pnext = NULL;
}



/*****************************************************************************
*   Prototype    : emptyListNode
*   Description  : if the list node is null or listnode->data is null return
                   null
*   Input        : pListNode p_l_node
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
bool emptyListNode( pListNode p_l_node )
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
*   Input        : pListNode list_node
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
void freeListNode( pListNode list_node )
{
    freeNode(list_node->pdata);
    free(list_node);
    list_node->pnext = NULL;
}

/*****************************************************************************
*   Prototype    : equal2listnodes
*   Description  : confirm the two list node is equal
*   Input        : pListNode one
*                  pListNode two
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
bool equal2ListNodes( pListNode one, pListNode two )
{
    if(one->pdata->id  == two->pdata->id)
    {
        return TRUE;
    }
    return FALSE;
}


