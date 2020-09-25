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
*   Input        : uint32 alloc_length
*                  uint32 elem_size
*                  void (* freefunc)(void *)
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
pCycleArray cycle_array_create(uint32 alloc_length ,uint32 elem_size,void (* freefunc)(void *)  )
{
    pCycleArray parray = (pCycleArray)Malloc(sizeof(CycleArray_t));
    //init   alloc  elems space
    parray->alloc_length = alloc_length;
    //init the array have no elems 
    parray->length = 0;
    parray->elem_size = elem_size;
    //for the free space then free the elems space
    parray->freefn = freefunc;
    parray->elems = Malloc( parray->alloc_length * parray->elem_size);
    assert(parray->elems != NULL);
}

/*****************************************************************************
*   Prototype    : cycle_array_destory
*   Description  : destory a cycle array
*   Input        : pCycleArray parray
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/19
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_array_destory( pCycleArray parray )
{
    if(NULL != parray->freefn )
    {
        //for Clear and clean
        for(int i = 0;i<parray->alloc_length;++i)
        {
            void* elem_addr =  parray->elems + i * parray->elem_size;
            parray->freefn(elem_addr);
        }
    }
    free(parray->elems);
    return TRUE;
}








