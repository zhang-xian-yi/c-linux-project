#include "./SList.h"

/*****************************************************************************
*   Prototype    : slist_create
*   Description  : create a single list
*   Input        : 
*   Output       : None
*   Return Value : pSList
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
pSList slist_create( )
{
    D_TRACE("single list create start\n");
    pSList list = NULL;
    do
    {
        //malloc a memery 
        pSList list = (pSList)Malloc(sizeof(SList_t));
        //create a header node
        pSListNode header = (pSListNode)Malloc(sizeof(SListNode_t));
        if(NULL == header || NULL == list)
        {
            break;
        }
        list->phead = header;
        list->p_pos  = header;
        
        //assign the list length
        list->list_length = 0;
        D_TRACE("single list create succ\n");
        return list;
    }while(FALSE);
    D_TRACE("single list create failed");
    slist_destory(list);
}


/*****************************************************************************
*   Prototype    : slist_destory
*   Description  : destory the single list and free memery
*   Input        : pSList list
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
bool slist_destory( pSList plist )
{
    D_TRACE("single list destory start\n");
    if( TRUE == slist_empty(plist) )
    {
        freeSListNode(plist->phead);
        free(plist);
        D_TRACE("single list destory end\n");
        return TRUE;
    }
    //realse middle node
    pSListNode temp = plist->phead->pnext;
    while(temp != plist->p_pos)
    {
        pSListNode temp_next= temp->pnext;
        //destory a list node and free it
        freeSListNode(temp);
        //change the current temp pos
        temp = temp_next;
    }
    D_TRACE("single list many nodes had free it\n");
    //realse start and end node
    freeSListNode(plist->phead);
    plist->phead = NULL;
    freeSListNode(plist->p_pos);
    plist->p_pos = NULL;
    //realse list  and clean zero
    memset(plist,0,sizeof(SList_t));
    free(plist);
    D_TRACE("single list destory end\n");
    return TRUE;
}


/*****************************************************************************
*   Prototype    : slist_add
*   Description  : add a single list node 
*   Input        : pSList plist
*                  pSListNode node
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
bool slist_add( pSList plist, pSListNode node )
{
    //organization the relation
    plist->p_pos->pnext = node;  
    plist->p_pos = node;
    plist->list_length++;
    D_TRACE("add data succ...\n");
    return TRUE;
}

/*****************************************************************************
*   Prototype    : slist_empty
*   Description  : confirm the list is empty
*   Input        : pSList plist
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
bool slist_empty( pSList plist )
{
    if(NULL == plist)
    {
        return TRUE;
    }
    if(plist->p_pos == plist->phead  )
    {
        return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
*   Prototype    : slist_del
*   Description  : delete a list node 
*   Input        : pSList list
*                  pSListNode temp
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
bool slist_del(pSList plist, pSListNode del_node )
{
    if (slist_empty(plist)) 
    {
        D_TRACE("empty queue£¬operation error...\n");
        exit(-1);
    }
    //save the del_node`s front node
    pSListNode p_temp= plist->phead;
    //if search a node but the list end
    while( TRUE != equal2SListNodes(p_temp, plist->p_pos))
    {
        //if not search the list end and find the del node
        if(TRUE == equal2SListNodes(p_temp->pnext, del_node))
        {
            //save the delnode`s next node
            pSListNode temp_next = del_node->pnext;
            freeSListNode(del_node);
            //the del_node`s front node  pointed the del_node`s next node
            p_temp->pnext = temp_next;
            D_TRACE("out node succ\n");
            plist->list_length --;
            return TRUE;
        }
        p_temp = p_temp->pnext;
    }
    
    D_TRACE("out node failed because not having the node\n");
    return FALSE;
}


/*****************************************************************************
*   Prototype    : getSListNode
*   Description  : get a list node by data id
*   Input        : pSList plist
*                  uint32 id
*   Output       : None
*   Return Value : pSListNode
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
pSListNode getSListNode(pSList plist , uint32 i_id )
{
    //temp pointer 
    pSListNode node= plist->phead->pnext;
    //if the head 
    if(node->pdata->id == i_id)
    {
        D_TRACE("search node succ\n");
        return node;
    }
    //if search a node but the list end
    while( TRUE != equal2SListNodes(node, plist->p_pos) )
    {
        //search a same node
        if(node->pdata->id == i_id)
        {
            D_TRACE("for each search node succ\n");
            return node;
        }
        node = node->pnext;
    }
    D_TRACE("search node failed \n");
    return NULL;
}


/*****************************************************************************
*   Prototype    : slist_control
*   Description  : control the search all nodes and opertial
*   Input        : pSList plist
*                  slist_oper_pfun* func
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
bool slist_control( pSList plist, slist_oper_pfun func_control,uint32 node_id)
{
    //traver the slist 
    pSListNode temp = plist->phead;
    while(temp != plist->p_pos)
    {
        pSListNode temp_next= temp->pnext;
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

