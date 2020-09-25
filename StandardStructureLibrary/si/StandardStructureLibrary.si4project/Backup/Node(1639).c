#include "./Node.h"
/*****************************************************************************
*   Prototype    : equals2Node
*   Description  : compare two nodes is equal
*   Input        : pNode one
*                  pNode two
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/1
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool equals2Node( pNode one, pNode two )
{
    if(one->id == two->id)
    {
        return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
*   Prototype    : compare2Node
*   Description  : compare two nodes return big or small
*   Input        : pNode one
*                  pNode two
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/1
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int compare2Node( pNode one, pNode two )
{
    if( TRUE == equals2Node(one,two) )
    {
        return EQUAL;
    }
    
    if(one->id > two->id)
    {
        return BIGGER;
    }
    else if(one->id < two->id)
    {
        return SMALLER;
    }
}

   
/*****************************************************************************
*   Prototype    : setNode
*   Description  : set the node and assign it
*   Input        : p_list_node p_l_node
                   uint32 id
*                  uint32 size
*                  void* node
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
void setNode(pNode p_node, uint32 id, uint32 i_size, void* node )
{
    p_node->id = id;
    p_node->size = i_size;
    p_node->pnode = node;
    //first assign it if  not equall 0 
    if(p_node->id < 0 || p_node->size < 0)
    {
        p_node->id = 0;
        p_node->size = 0;
    }
}

/*****************************************************************************
*   Prototype    : isEmptyNode
*   Description  : empty the node data is null
*   Input        : pNode node
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
bool isEmptyNode( pNode node )
{
    if(NULL == node)
    {
        return TRUE;
    }
    if(NULL == node->pnode)
    {
        return TRUE;
    }
    return FALSE;
}


/*****************************************************************************
*   Prototype    : freeNode
*   Description  : free a node 
*   Input        : pNode node
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
bool freeNode( pNode node )
{
    if( TRUE == isEmptyNode(node) )
    {
        //free the pNode;
        free(node);
        return;
    }
    node->size = 0;
    //if the pnode is not empty must free the pointer
    free(node->pnode);
    node->pnode = NULL;
    //free the pNode;
    free(node);
    return;
}

/*****************************************************************************
*   Prototype    : getNodeMem
*   Description  : get a node memery by input parameter
*   Input        : uint32 id
*                  uint32 size
*                  void* args
*   Output       : None
*   Return Value : pNode
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
pNode getNodeMem( uint32 i_id, uint32 i_size, void* args )
{
    pNode temp = (pNode)malloc(sizeof(Node_t));
    setNode(temp, i_id, i_size, args);
    return temp;
}

/*****************************************************************************
*   Prototype    : deepCopyNode
*   Description  : get the deep copy node mem
*   Input        : None
*   Output       : None
*   Return Value : pNode
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/10
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pNode deepCopyNode(pNode i_node)
{
    pNode temp = (pNode)malloc(sizeof(Node_t));
    temp->id = i_node->id;
    temp->size = i_node->size;
    /* BEGIN: Modified for PN:1 by zhangxianyi, 2020/5/16 */
    memcpy(temp->pnode,i_node,temp->size);
    return temp;
    /* END:   Modified for PN:1 by zhangxianyi, 2020/5/16 */
}
