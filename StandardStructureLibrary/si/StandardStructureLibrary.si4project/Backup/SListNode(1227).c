#include "./include/SListNode.h"

/*****************************************************************************
*   Prototype    : compare2
*   Description  : compare two list node 
*   Input        : p_list_node one
*                  p_list_node two
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
int compare2( p_list_node one, p_list_node two )
{
    //return bigger mean one id > two id
    return compare2Node(one->pdata, two->pdata);
}

/*****************************************************************************
*   Prototype    : setListNode
*   Description  : set the pdata and assign it
*   Input        : p_list_node p_l_node
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
void setListNode(p_list_node p_l_node, pNode data)
{
    setNode(p_l_node->pdata, data->id, data->count, data->pnode);
    p_l_node->pnext = NULL;
}



/*****************************************************************************
*   Prototype    : emptyListNode
*   Description  : if the list node is null or listnode->data is null return
                   null
*   Input        : p_list_node p_l_node
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
bool emptyListNode( p_list_node p_l_node )
{
    //input null node 
    if(NULL == p_l_node )
    {
        return TRUE;
    }
    //confirm the pdata is not null    
    return isEmptyNode(p_l_node->pdata);
}




