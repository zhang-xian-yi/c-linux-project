/******************************************************************************
*
*  Copyright (C), 2015-2025, mengxing Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : NodeSequence.c
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/6/6
*  Last Modified :
*  Description   : c file fro node sequence
*  Function List :
*
*       1.                getIndex
*       2.                nSequence_add
*       3.                nSequence_control
*       4.                nSequence_create
*       5.                nSequence_del
*       6.                nSequence_destory
*       7.                nSequence_get
*       8.                nSequence_grow
*
*  History:
* 
*       1.  Date         : 2020/6/6
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./nodes/base/Node.h"
#include <assert.h>
#include "./NodeSequence.h"




/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/



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
    static pNode addr = NULL;
    for(int i = 0;i < pNSeq->alloc_num;++i)
    {
        //because only need void* addr  not use * 0x0  so
        addr = (* (pNode*) (pNSeq->elems + i ) );
        //pointer + 1  mean move the size of alt type  
        if( FALSE ==  isEmptyNode( addr ) )
        {
            if(nid == addr->id)
            {
                return i;
            }
        }
        else
        {
            return i;         
        }
        addr = NULL;
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
    
    static pNode addr = NULL;
    for(int i = 0;i<pNSeq->alloc_num;++i)
    {
        addr = (* (pNode*) (pNSeq->elems + i ) );
        if(FALSE == isEmptyNode( addr ) )
        {
            pNSeq->freeNodefn(addr);
            //memset(addr,0,pNSeq->elem_size);
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
        pNode* dest = pNSeq->elems;
        dest[index] = node;
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
    uint32 index = getIndex(pNSeq, nid);
    bool ret = FALSE;
    //exist the node 
    if(NOT_EXIST != index)
    {
        ret = pNSeq->freeNodefn(pNSeq->elems[index]);
        //pNSeq->elems[index] = 0x0;
        pNSeq->elem_num -- ;
    }
    //confire the array is senquence     and  middle not have 0x0 pointer
    for(int temp_index = index;temp_index < pNSeq->alloc_num - 1;++temp_index)
    {
        //move the array value to left
        pNSeq->elems[temp_index] = pNSeq->elems[temp_index + 1];
    }
    pNSeq->elems[pNSeq->alloc_num - 1] = 0x0;
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
    return *((pNode*)(pNSeq->elems + index));
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
    uint32 zero_size = (pNSeq->alloc_num - pNSeq->elem_num) * pNSeq->elem_size; 
    memset(pNSeq->elems + pNSeq->elem_num, 0 ,zero_size);
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
    static pNode addr = NULL;
    static bool ret = FALSE;
    for(int i = 0; i < pNSeq->elem_num;++i)
    {
        addr = pNSeq->elems + i;
        if(nid == addr->id)
        {
            ret = operafn(addr->id,nid);
        }
    }
    return ret;
}











