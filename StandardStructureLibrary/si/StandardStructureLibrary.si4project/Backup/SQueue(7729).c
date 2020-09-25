#include"./SQueue.h"

/*****************************************************************************
*   Prototype    : squeue_add
*   Description  : add a queue node tu squeue
*   Input        : pQueue queue
*                  QueueNode_t node
*   Output       : None
*   Return Value : bool
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
bool squeue_add( pQueue pqueue, pQueueNode node)
{
    slist_add(pqueue->psqueue, node);
    pqueue->plast = node;
    return TRUE;
}

/*****************************************************************************
*   Prototype    : squeue_create
*   Description  : create a sing queue
*   Input        : None
*   Output       : None
*   Return Value : pQueue
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
pQueue squeue_create(  )
{
    pQueue pqueue = (pQueue)Malloc(sizeof(SQueue_t));
    pSList pslist = slist_create();
    pqueue->psqueue = pslist;
    pqueue->pfrist = pslist->phead;
    pqueue->plast = pslist->p_pos;

    return pqueue;
}


/*****************************************************************************
*   Prototype    : squeue_destory
*   Description  : destory a queue
*   Input        : pQueue queue
*   Output       : None
*   Return Value : bool
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
bool squeue_destory( pQueue pqueue )
{
    bool ret =slist_destory(pqueue->psqueue);
    //clear zero
    memset(pqueue,0,sizeof(SQueue_t));
    free(pqueue);
    return ret;
}

/*****************************************************************************
*   Prototype    : deepCopy2QueueNode
*   Description  : deep copy the queue node 
*   Input        : pQueueNode one
*   Output       : None
*   Return Value : pQueueNode
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
static pQueueNode deepCopyQueueNode( pQueueNode one )
{
    pQueueNode temp = (pQueueNode)Malloc(sizeof(QueueNode_t));
    temp = getSListNodeMem2(one->pdata->id, one->pdata->count, one->pdata->pnode);
    //deep copy the base node mem
    //temp->pdata->pnode = deepCopyNode(one->pdata->pnode, sizeof(Task_t));
    return temp;
}

/*****************************************************************************
*   Prototype    : squeue_pop
*   Description  : delete a node by phead->pnext
*   Input        : pQueue pqueue
*   Output       : None
*   Return Value : pQueueNode
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
void squeue_pop(pQueue pqueue )
{
    slist_del(pqueue->psqueue, pqueue->pfrist->pnext);
    pqueue->pfrist = ( pqueue->psqueue->phead);
}


/*****************************************************************************
*   Prototype    : squeue_control
*   Description  : control the sraech the all queue node and operated it
*   Input        : pQueue queue
*                  queue_oper_func func_control
*                  uint32 n_id
*   Output       : None
*   Return Value : bool
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
bool squeue_control( pQueue pqueue ,queue_oper_func func_control,uint32 n_id)
{
    //traver the slist 
    pQueueNode temp = pqueue->pfrist;
    while(temp != pqueue->plast)
    {
        pQueueNode temp_next= temp->pnext;
        //opertion the func
        if (TRUE == func_control(temp,n_id)  )
        {
            return TRUE;
        }
        //change the current temp pos
        temp = temp_next;
    }
    return FALSE;
}

/*****************************************************************************
*   Prototype    : getQueueNodeMem
*   Description  : get the queue node memery
*   Input        : uint32 id
*                  uint32 count
*                  void* args
*   Output       : None
*   Return Value : pQueueNode
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
pQueueNode getQueueNodeMem( uint32 id, uint32 count, void* args )
{
    return getSListNodeMem2(id, count, args);
}
