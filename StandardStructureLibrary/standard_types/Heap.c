#include<stdlib.h>
#include<time.h>

#include "./base_types/nodes/base/Node.h"
#include "./base_types/nodes/wrap.h"


//use union change variable name   


typedef struct _T_Heap
{
    uint16   node_num;
    uint16   alloc_num;
    pNode    *arr;    //save the pNode  array    
}Heap_t;

typedef Heap_t*  pHeap;
/*****************************************************************************
*   Prototype    : heap_create
*   Description  : create a heap
*   Input        : Node
*   Output       : None
*   Return Value : pHeap
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
pHeap heap_create(  )
{
    pHeap heap = (pHeap)Malloc(sizeof(Heap_t));
    heap->alloc_num = 32;
    heap->node_num = 0;
    heap->arr = (pNode*)Malloc( sizeof(Node_t) * heap->alloc_num);

    return heap;
}







