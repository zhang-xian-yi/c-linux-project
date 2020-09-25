#include "./DCycleList.h"

/*****************************************************************************
*   Prototype    : cycle_list_create
*   Description  : create a cycle list
*   Input        : void
*   Output       : None
*   Return Value : pCycleList
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/13
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pCycleList cycle_list_create( void )
{
    pCycleList  plist = (pCycleList)Malloc(sizeof(CycleListNode_t));
    pCycleListNode  header = (pCycleListNode)Malloc(sizeof(CycleListNode_t));
    plist->list_length = 0;
    plist->phead = header;
    plist->ptail = header;
    return plist;
}

/*****************************************************************************
*   Prototype    : cycle_list_destory
*   Description  : destory a cycle list and free it
*   Input        : pCycleList
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/13
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_list_destory( pCycleList  plist)
{
    if( TRUE == cycle_list_empty(plist) )
    {
        freeDListNode(plist->phead);
        free(plist);
        D_TRACE("double list destory end\n");
        return TRUE;;
    }
    //realse middle node
    pCycleListNode temp = plist->phead->pnext;
    while(temp != plist->ptail)
    {
        //get the really first node`s next
        pCycleListNode temp_next= temp->pnext;
        //destory a list node and free it
        freeDListNode(temp);
        //change the current temp pos
        temp = temp_next;
    }
    D_TRACE("double list many nodes had free it\n");
    //realse start and end node
    freeDListNode(plist->phead);
    plist->phead = NULL;
    freeDListNode(plist->ptail);
    plist->ptail = NULL;
    //realse list  and clean zero
    memset(plist,0,sizeof(DCycleList_t));
    free(plist);
    return TRUE;
}


/*****************************************************************************
*   Prototype    : cycle_list_control
*   Description  : control the cycle list
*   Input        : pCycleList plist
*                  cycle_list_func_oper func
*                  uint32 nid
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/13
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_list_control( pCycleList plist, cycle_list_func_oper func ,uint32 nid)
{
    //realse middle node
    pCycleListNode temp = plist->phead->pnext;
    while(temp != plist->ptail)
    {
        //get the really first node`s next
        pCycleListNode temp_next= temp->pnext;
        //oper the list every node

        /* BEGIN: Modified for PN:1 by zhangxianyi, 2020/5/16 */
        func(temp,nid);
        /* END:   Modified for PN:1 by zhangxianyi, 2020/5/16 */

        //change the current temp pos
        temp = temp_next;
    }
    func(plist->ptail,nid);
    return TRUE;
}

/*****************************************************************************
*   Prototype    : cycle_list_empty
*   Description  : confirm the cycle list is empty or not
*   Input        : pCycleList plist
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/16
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_list_empty( pCycleList plist )
{
    bool ret = FALSE;
    // NULL pointer is empty list
    if( NULL == plist)
    {
        ret = TRUE;
    }
    //list length == 0  is empty list
    if( 0 == plist->list_length)
    {
        ret = TRUE;
    }
    //phead == ptail   head pointer is empty  
    if(plist->phead == plist->ptail)
    {
        ret = TRUE;
    }
    return ret;
}

/*****************************************************************************
*   Prototype    : cycle_list_full
*   Description  : confirm the cycle list is full or not
*   Input        : pCycleList plist
*                  uint32 list_length
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/16
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_list_full( pCycleList plist,uint32 list_length )
{
    bool ret = FALSE;
    //if the list head`next node  == the tail`next node mean full list 
    if(list_length == plist->list_length)
    {
        ret = TRUE;
    }
    return ret;
}

/*****************************************************************************
*   Prototype    : cycle_list_add
*   Description  : add a cycle list node in plist
*   Input        : pCycleList plist
*                  uint32 list_length
*                  pCycleListNode node
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/16
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_list_add( pCycleList plist, uint32 list_length,pCycleListNode node )
{
    //if the list is empty  
    if(NULL != plist  && TRUE == cycle_list_empty(plist))
    {
        plist->ptail->pnext = node;
        plist->ptail = node;
        plist->list_length ++;
        return TRUE;
    }
    else if(TRUE == cycle_list_full(plist,list_length))
    {
        return FALSE;
    }
    else
    {
        //the list is not fulle  also is not empty
        plist->ptail->pnext = node;
        node->pfront = plist->ptail;
        //change the ptail pointer
        plist->ptail = node;
        //orginazed the cycle relationship
        plist->ptail->pnext = plist->phead->pnext;
        plist->list_length ++;
        return TRUE;
    }
}


/*****************************************************************************
*   Prototype    : cycle_list_del
*   Description  : delete a cycle list node in list from ptail
*   Input        : pCycleList plist
*                  pCycleListNode del_node
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/16
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_list_del( pCycleList plist, pCycleListNode del_node )
{
    if (cycle_list_empty(plist)) 
    {
        D_TRACE("empty cycle list£¬operation error...\n");
        exit(-1);
    }
    //save the del_node`s front node
    pCycleListNode p_temp= plist->phead;
    //if search a node but the list end
    while( TRUE != equal2CycleListNode(p_temp, plist->ptail))
    {
        //if not search the list end and find the del node
        if(TRUE == equal2CycleListNode(p_temp->pnext, del_node))
        {
            //save the delnode`s next node
            pCycleListNode temp_next = del_node->pnext;
            freeDListNode(del_node);
            //the del_node`s front node  pointed the del_node`s next node
            p_temp->pnext = temp_next;
            temp_next->pfront = p_temp;
            D_TRACE("out node succ\n");
            plist->list_length --;
            //originazed the cycle relationship
            plist->ptail->pnext = plist->phead->pnext;
            return TRUE;
        }
        p_temp = p_temp->pnext;
    }
    
    return FALSE;
}

/*****************************************************************************
*   Prototype    : equal2CycleListNode
*   Description  : confirm the 2 list node is equal or not
*   Input        : pCycleListNode one
*                  pCycleListNode two
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/16
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool equal2CycleListNode( pCycleListNode one, pCycleListNode two )
{
    return equal2DListNode(one, two);
}


/*****************************************************************************
*   Prototype    : getCycleListNodeMem
*   Description  : get a cycle list node memery
*   Input        : uint32 id
*                  uint32 size
*                  void* data
*   Output       : None
*   Return Value : pCycleListNode
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/16
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pCycleListNode getCycleListNodeMem( uint32 id, uint32 size, pNode node )
{
    return getDListNodeMem(id, size, node);
}
