#include "./base_types/nodes/wrap.h"
#include "./base_types/nodes/base/public.h"

#include <assert.h>


typedef struct 
{
    int length;           //array elem num
    int alloc_length;     //alloc the elem memery length  
    int elem_size;       //elem size
    void * elems;          //array space start addr
    void (* freefn)(void *); // free the memery func pointer
} CycleArray_t;

typedef CycleArray_t*   pCycleArray;

/*****************************************************************************
*   Prototype    : cycle_array_create
*   Description  : create a cycle array 
*   Input        : 
*
*
*
*   Output       : None
*   Return Value : pCycleArray
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/18
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pCycleArray cycle_array_create(pCycleArray parray ,uint32 elem_size,void (* freefunc)(void *)  )
{
    //init   alloc 4 elems space
    parray->alloc_length = 4;
    //init the array have no elems 
    parray->length = 0;
    parray->elem_size = elem_size;
    //for the free space then free the elems space
    parray->freefn = freefunc;
    parray->elems = Malloc( 4 * elem_size);
    assert(parray->elems != NULL);
}






