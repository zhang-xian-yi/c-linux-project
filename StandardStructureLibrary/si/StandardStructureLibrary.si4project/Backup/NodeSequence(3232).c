#include "./nodes/base/Node.h"
#include <assert.h>
#include "./NodeSequence.h"


/*****************************************************************************
*   Prototype    : getIndex
*   Description  : from node sequence get index by node id
*   Input        : pNSequence pNseq
*                  uint32 nid
*   Output       : None
*   Return Value : uint32
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/5
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
static uint32 getIndex( pNSequence pNSeq, uint32 nid )
{
    for(int i = 0;i < pNSeq->alloc_num;++i)
    {
        //because only need void* addr  not use * 0x0  so
        pNode addr = *(pNode*)(pNSeq->elems + i * pNSeq->elem_size);
        if(NULL != addr)
        {
            uint32 temp_id = addr->id;
            if(nid == temp_id)
            {
                return i;
            }
        }
        else
        {
            return i;            
        }
        
    }
    return NOT_EXIST;
}



/*****************************************************************************
*   Prototype    : nSequence_create
*   Description  : create a node sequence
*   Input        : uint32 node_nums               
*                  uint32 node_size               
*                  bool(*freeNodefn)(pNode elem)  
*   Output       : None
*   Return Value : pNSequence
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/5
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pNSequence nSequence_create(uint32 node_nums,uint32 node_size, bool(*freeNodefn)(pNode elem) )
{
    pNSequence pNSeq = (pNSequence)Malloc(sizeof(NSequence_t));
    //init the 8 nodes  memery 
    pNSeq->alloc_num = node_nums;
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
*       1.  Date         : 2020/6/5
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
    
    pNode arr[] = pNSeq->elems;
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
    uint32 index = getIndex(pNSeq, EMPTY_NODE_ID);
    if(pNSeq->elem_num < pNSeq->alloc_num)
    {
        //get the dest addr by empty index 
        void* dest = pNSeq->elems + index * pNSeq->elem_size;
        memcpy(dest, &node, sizeof(pNode));
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
pNode  nSequence_get( pNSequence pNSeq, uint32 nid )
{
    uint32 index = getIndex(pNSeq, nid);
    return *((pNode*)(pNSeq->elems + index * pNSeq->elem_size));
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


/*****************************************************************************
*   Prototype    : nSequence_control
*   Description  : control every sequence node operated
*   Input        : pNSequence pNSeq
*                  bool (*operafn)(pNode one,uint32 nid)
*                  uint32 nid
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/30
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool nSequence_control( pNSequence pNSeq, bool (*operafn)(pNode one,uint32 nid), uint32 nid )
{
    for(int i = 0; i < pNSeq->elem_num;++i)
    {
        uint32 temp_id = (*(pNode*)(pNSeq->elems + i * pNSeq->elem_size))->id;
        if(nid == temp_id)
        {
            operafn(pNSeq->elems[i]->id,nid);
        }
    }
}











