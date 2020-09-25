#include "./nodes/DListNode.h"
#include "./nodes/wrap.h"

#include "./DList.h"


typedef struct _T_LinkList
{
    pDListNode                phead;
    pDListNode                p_pos;
    uint32                    list_length;
}DList_t;

typedef DList_t*   pDList;


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
        D_TRACE("single list create succ\n");
        return list;
    }while(FALSE);
    D_TRACE("single list create failed");
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


