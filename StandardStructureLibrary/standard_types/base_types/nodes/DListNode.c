#include "./DListNode.h"

const uint8 max_length = 100;

/*****************************************************************************
*   Prototype    : getDListNodeMem
*   Description  : get the double list node memery by id ,size pnode
*   Input        : uint32 id
*                  uint32 size
*                  pNode pnode
*   Output       : None
*   Return Value : pDListNode
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/7
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pDListNode getDListNodeMem( uint32 id, uint32 size, pNode pnode )
{
    pNode node = getNodeMem(id, size, pnode);
    pDListNode temp = (pDListNode)Malloc(sizeof(DListNode_t));
    //assign the temp value
    temp->pdata =node;
    temp->pfront = NULL;
    temp->pnext = NULL;

    return temp;
}

/*****************************************************************************
*   Prototype    : emptyDListNode
*   Description  : confirm the dlist node is null or not
*   Input        : pDListNode i_node
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/7
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool emptyDListNode( pDListNode i_node )
{
    if(i_node == NULL || isEmptyNode(i_node->pdata))
    {
        return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
*   Prototype    : freeDListNode
*   Description  : free a double list node memery
*   Input        : pDListNode i_dn
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/7
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void freeDListNode( pDListNode i_dn )
{
    //free the pNode
    freeNode(i_dn->pdata);
    i_dn->pdata = NULL;
    i_dn->pnext = NULL;
    i_dn->pfront = NULL;
    //free the double list  node
    free(i_dn);
}

/*****************************************************************************
*   Prototype    : equal2DListNode
*   Description  : confirm the 2 double list node is equal
*   Input        : pDListNode one  
*                  pDListNode two  
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/8
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool equal2DListNode(pDListNode one,pDListNode two)
{
    if(emptyDListNode(one) || emptyDListNode(two))
    {
        return FALSE;
    }
    //compare the id 
    if(one->pdata->id  == two->pdata->id)
    {
        return TRUE;
    }
    return FALSE;
}
/*****************************************************************************
*   Prototype    : compare2DListNode
*   Description  : compare the 2 double list node 
*   Input        : pSListNode one  
*                  pSListNode two  
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/8
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int compare2DListNode( pDListNode one, pDListNode two )
{
    return compare2Node(one->pdata, two->pdata);
}








