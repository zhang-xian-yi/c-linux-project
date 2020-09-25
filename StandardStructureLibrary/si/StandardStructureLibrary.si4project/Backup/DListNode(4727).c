#include "./base/Node.h"
#include "./wrap.h"

#include "./DListNode.h"

typedef struct  _T_DListNode
{
	pNode                  pdata;
	struct _T_DListNode*   pfront;
	struct _T_DListNode*   pnext;
}DListNode_t;

typedef DListNode_t* pDListNode;

/*****************************************************************************
*   Prototype    : getDListNodeMem
*   Description  : get the double list node memery by id ,count pnode
*   Input        : uint32 id
*                  uint32 count
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
pDListNode getDListNodeMem( uint32 id, uint32 count, pNode pnode )
{
    pNode node = getNodeMem(id, count, pnode);
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
bool freeDListNode( pDListNode i_dn )
{
    
}







