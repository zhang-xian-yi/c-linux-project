#include "./DList.h"
/*****************************************************************************
*   Prototype    : dlist_create
*   Description  : create a double list 
*   Input        : None
*   Output       : None
*   Return Value : pDList 
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/9
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pDList  dlist_create(  )
{
    D_TRACE("double list create start\n");
    pDList list = NULL;
    do
    {
        //malloc a memery 
        pDList list = (pDList)Malloc(sizeof(DList_t));
        //create a header node
        pDListNode header = (pDListNode)Malloc(sizeof(DListNode_t));
        if(NULL == header || NULL == list)
        {
            break;
        }
        list->phead = header;
        list->p_pos  = header;
        
        //assign the list length
        list->list_length = 0;
        D_TRACE("double list create succ\n");
        return list;
    }while(FALSE);
    D_TRACE("double list create failed");
    dlist_destory(list);
}


/*****************************************************************************
*   Prototype    : dlist_destory
*   Description  : destory a double list
*   Input        : pDList pdlist
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/9
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void dlist_destory( pDList pdlist )
{
    D_TRACE("double list destory start\n");
    if( TRUE == dlist_empty(pdlist) )
    {
        freeDListNode(pdlist->phead);
        free(pdlist);
        D_TRACE("double list destory end\n");
        return;
    }
    //realse middle node
    pDListNode temp = pdlist->phead->pnext;
    while(temp != pdlist->p_pos)
    {
        //get the really first node`s next
        pDListNode temp_next= temp->pnext;
        //destory a list node and free it
        freeDListNode(temp);
        //change the current temp pos
        temp = temp_next;
    }
    D_TRACE("double list many nodes had free it\n");
    //realse start and end node
    freeDListNode(pdlist->phead);
    pdlist->phead = NULL;
    freeDListNode(pdlist->p_pos);
    pdlist->p_pos = NULL;
    //realse list  and clean zero
    memset(pdlist,0,sizeof(DList_t));
    free(pdlist);
    D_TRACE("double list destory end\n");
    return;
}

/*****************************************************************************
*   Prototype    : dlist_empty
*   Description  : confrim the double list is null or not
*   Input        : pDList pdlist
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/9
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool dlist_empty( pDList pdlist )
{
    if(NULL == pdlist)
    {
        return TRUE;
    }
    if(pdlist->p_pos == pdlist->phead )
    {
        return TRUE;
    }
    if(0 == pdlist->list_length)
    {
        return TRUE;
    }
    return FALSE;
}


/*****************************************************************************
*   Prototype    : dlist_add
*   Description  : add a double list node into pdlist
*   Input        : pDList pdlist
*                  pDListNode node
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/9
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool dlist_add( pDList pdlist, pDListNode node )
{
    //organization the relation
    pdlist->p_pos->pnext = node;
    node->pfront = pdlist->p_pos;
    //change the last node pointer postion
    pdlist->p_pos = node;
    pdlist->list_length++;
    D_TRACE("add data succ...\n");
    return TRUE;
}

/*****************************************************************************
*   Prototype    : dlist_del
*   Description  : delete a  double list node with temp 
*   Input        : pDList pdlist
*                  pDListNode del_node
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/9
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool dlist_del( pDList pdlist, pDListNode del_node )
{
    if (dlist_empty(pdlist)) 
    {
        D_TRACE("empty double list£¬operation error...\n");
        exit(-1);
    }
    //save the del_node`s front node
    pDListNode p_temp= pdlist->phead;
    //if search a node but the list end
    while( TRUE != equal2DListNode(p_temp, pdlist->p_pos))
    {
        //if not search the list end and find the del node
        if(TRUE == equal2DListNode(p_temp->pnext, del_node))
        {
            //save the delnode`s next node
            pDListNode temp_next = del_node->pnext;
            freeDListNode(del_node);
            //the del_node`s front node  pointed the del_node`s next node
            p_temp->pnext = temp_next;
            temp_next->pfront = p_temp;
            D_TRACE("out node succ\n");
            pdlist->list_length --;
            return TRUE;
        }
        p_temp = p_temp->pnext;
    }
    
    D_TRACE("out node failed because not having the node\n");
    return FALSE;
}


/*****************************************************************************
*   Prototype    : dlist_control
*   Description  : control the search all list and operated one node
*   Input        : pDList pdlist
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/9
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool dlist_control( pDList pdlist,dlist_oper_pfun func_control,uint32 node_id )
{
    //traver the slist 
    pDListNode temp = pdlist->phead;
    while(temp != pdlist->p_pos)
    {
        pDListNode temp_next= temp->pnext;
        //opertion the func
        if (TRUE == func_control(temp,node_id)  )
        {
            return TRUE;
        }
        //change the current temp pos
        temp = temp_next;
    }
    return FALSE;
}

/*****************************************************************************
*   Prototype    : getDListNode
*   Description  : get a double list node by nid
*   Input        : pDList pdlist
*                  uint32 nid
*   Output       : None
*   Return Value : pDListNode
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/9
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pDListNode getDListNode( pDList pdlist, uint32 nid )
{
    //temp pointer 
    pDListNode node= pdlist->phead;
    //if search a node but the list end
    while( TRUE != equal2SListNodes(node, pdlist->p_pos) )
    {
        //search a same node
        if(node->pnext->pdata->id == nid)
        {
            D_TRACE("for each search node succ\n");
            return node->pnext;
        }
        node = node->pnext;
    }
    D_TRACE("search node failed \n");
    return NULL;
}
