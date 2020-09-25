#include "./nodes/include/SListNode.h"
#include "./nodes/include/wrap.h"


typedef struct _T_LinkList
{
    pListNode                phead;
    pListNode                p_pos;
    uint32                   list_length;
}SList_t;

typedef SList_t*   pSList;


/*****************************************************************************
*   Prototype    : slist_create
*   Description  : create a single list
*   Input        : int length
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
pSList slist_create( int length )
{
    //malloc a memery 
    pSList list = (pSList)Malloc(sizeof(SList_t));
    do
    {
        //malloc a node to the base 
        list->phead = (pListNode)Malloc(sizeof(SListNode_t));

        //create a header node
        pListNode header = (pListNode)Malloc(sizeof(SListNode_t));
        list->phead = header;
        list->p_pos  = header;
        //create leaves node
        for(int i = 1;i<length;++i)
        {
           pListNode pNewNode = (pListNode)Malloc(sizeof(SListNode_t));
           list->p_pos->pnext = pNewNode;
           //change the list position pointer alt
           list->p_pos = pNewNode;
        }
        //assign the list length
        list->list_length = length;
        D_TRACE("single list create succ");
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
void slist_destory( pSList plist )
{
    if(NULL == plist)
    {
        return;
    }
    //realse middle node
    pListNode temp = plist->phead->pnext;
    while(temp != plist->p_pos)
    {
        pListNode temp_next= temp->pnext;
        //destory a list node and free it
        freeListNode(temp);
        //change the current temp pos
        temp = temp_next;
    }
    //realse start and end node
    freeListNode(plist->phead);
    freeListNode(plist->p_pos);

    //realse list  and clean zero
    memset(plist,0,sizeof(SList_t));
    free(plist);
    return;
}


/*****************************************************************************
*   Prototype    : slist_add
*   Description  : add a single list node 
*   Input        : pSList plist
*                  pListNode node
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
bool slist_add( pSList plist, pListNode node )
{
    //create a new node to storage new data
    pListNode t_Pnode = (pListNode)Malloc(sizeof(SListNode_t));    
    //seal the data
        //setListNode(node, node->pdata);
    //organization the relation 
    plist->p_pos->pnext = t_Pnode;    
    plist->p_pos = t_Pnode;
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
    if(NULL == plist || NULL == plist->phead  )
    {
        return TRUE;
    }
}

/*****************************************************************************
*   Prototype    : slist_del
*   Description  : delete a list node 
*   Input        : pSList list
*                  pListNode temp
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
bool slist_del(pSList plist, pListNode temp )
{
    if (slist_empty(plist)) 
    {
        D_TRACE("empty queue£¬operation error...\n");
        exit(-1);
    }
    //temp pointer 
    pListNode node= plist->phead;    
    //update the head node
    while()
    {
        
    }
    D_TRACE("out queue succ\n");
}


