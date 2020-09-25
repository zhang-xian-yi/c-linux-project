#include "./base_types/SList.h"
#include "./base_types/nodes/wrap.h"

typedef SListNode_t     QueueNode_t;
typedef pSListNode      pQueueNode;
 
typedef struct _T_SQUEUE
{
    SList_t         queue;
    pQueueNode      pfrist;
    pQueueNode      plast;
}SQueue_t;

typedef SQueue_t *   pQueue;


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
    slist_add(&(pqueue->queue), node);
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
    pqueue->queue = *pslist;
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
bool squeue_destory( pQueue queue )
{
    bool ret =slist_destory(queue->queue);
    queue->queue = NULL;
    queue->pfrist = NULL;
    queue->plast = NULL;
    free(queue);
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
pQueueNode deepCopy2QueueNode( pQueueNode one )
{
    pQueueNode temp = (pQueueNode)Malloc(sizeof(QueueNode_t));
    temp->pdata = getSListNodeMem2(one->pdata->id, uint32 count, void * pnode)
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
pQueueNode squeue_pop(pQueue pqueue )
{
    pQueueNode = getSListNodeMem2(pqueue->pfrist->pdata->id, pqueue->pfrist->pdata->count, pqueue->pfrist->pdata->pnode);
    slist_del(pqueue->queue, pqueue->pfrist);
    pqueue->pfrist = pqueue->queue->phead->pnext;
    
}
