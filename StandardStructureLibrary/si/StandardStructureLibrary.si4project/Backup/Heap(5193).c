#include<stdlib.h>
#include<time.h>

typedef struct _T_Heap
{
    uint16 node_num;     //heap has nums node
    uint16 node_size;
    uint16 alloc_num;
    void*  arr;
     
}Heap_t;

typedef Heap_t*  pHeap;
/*****************************************************************************
*   Prototype    : heap_create
*   Description  : create a heap
*   Input        : pNode arr[]
*                  uint16 size
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
pHeap heap_create( pNode arr[], uint16 size )
{
    
}





