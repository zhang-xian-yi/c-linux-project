#include "./nodes/base/Nnode.h"
#include <assert.h>

typedef struct _T_NodeSequence
{
    uint32 elem_num;
    uint32 elem_size;
    uint32 alloc_num;
    pNode*  elems;
    bool  (*freeNodefn)(pNode elem);
}NSequence_t;


typedef NSequence_t* pNSequence;


/*****************************************************************************
*   Prototype    : nSequence_create
*   Description  : create a node sequence
*   Input        : None
*   Output       : None
*   Return Value : pNSequence
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/29
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pNSequence nSequence_create( uint32 node_size, bool(*freeNodefn)(pNode elem) )
{
    pNSequence pNSeq = (pNSequence)Malloc(sizeof(NSequence_t));
    //init the 8 nodes  memery 
    pNSeq->alloc_num = 8;
    pNSeq->elem_num = 0;
    pNSeq->elem_size = node_size;
    pNSeq->freeNodefn = freeNodefn;
    pNSeq->elems = (pNode*)Malloc(sizeof(pNode) * pNSeq->alloc_num);
    assert(pNSeq->elems != NULL);
    return pNSeq;
}


/*****************************************************************************
*   Prototype    : nSequence_destory
*   Description  : destory a node sequence 
*   Input        : pNSequence pNSeq
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/29
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool nSequence_destory( pNSequence pNSeq )
{
    if(NULL == pNSeq->freeNodefn)
    {
        assert(pNSeq->freeNodefn);
        return FALSE;
    }
    
    pNode* arr = pNSeq->elems;
    for(int i = 0;i<pNSeq->alloc_num;++i)
    {
        if(! isEmptyNode(arr[i]))
        {
            pNSeq->freeNodefn(arr[i]);
            arr[i] = NULL;
        }
    }
    free(pNSeq->elems);
    pNSeq->elems = NULL;
    free(pNSeq);
    pNSeq = NULL;
    return TRUE;
}

/*****************************************************************************
*   Prototype    : nSequence_add
*   Description  : add a node into Sequence
*   Input        : pNSequence pNSeq
*                  pNode node
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/29
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool nSequence_add( pNSequence pNSeq, pNode node )
{
    //get a first empty node index
    uint32 index = nSequence_get(pNSeq, EMPTY_NODE_ID);
    if(pNSeq->elem_num < pNSeq->alloc_num)
    {
        pNSeq->elems[index] = node;
        pNSeq->elem_num ++;
        return TRUE;    
    }
    else //if(pNSeq->elem_num >= pNSeq->alloc_num)
    {
        D_TRACE("the sequence is full ");
        return FALSE;
    }
    
}

/*****************************************************************************
*   Prototype    : nSequence_del
*   Description  : del a node from sequence and free it  by node id
*   Input        : pNSequence pNSeq
*                  uint32 nid
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/29
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool nSequence_del( pNSequence pNSeq, uint32 nid )
{
    uint32 index = nSequence_get(pNSeq, nid);
    bool ret = FALSE;
    //exist the node 
    if(NOT_EXIST != index)
    {
        ret = freeNode(pNSeq->elems[index]);
        pNSeq->elem_num -- ;
    }
    return ret;
}


/*****************************************************************************
*   Prototype    : nSequence_get
*   Description  : get a node from node sequence by node id
*   Input        : pNSequence pNSeq
*                  uint32 nid
*   Output       : None
*   Return Value : pNode 
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/29
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
uint32  nSequence_get( pNSequence pNSeq, uint32 nid )
{
    for(int i = 0;i < pNSeq->elem_num;++i)
    {
        if(nid == pNSeq->elems[i]->id)
        {
            return i;
        }
    }
    return NOT_EXIST;
}

/*****************************************************************************
*   Prototype    : nSequence_grow
*   Description  : grow the sequence memery
*   Input        : pNSequence pNSeq
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/29
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool nSequence_grow( pNSequence pNSeq )
{
    //grow the array for 2 times
    pNSeq->alloc_num *= 2;
    pNSeq->elems = Realloc(pNSeq->elems,pNSeq->alloc_num * pNSeq->elem_size);
    assert(pNSeq->elems);
    return TRUE;
}









