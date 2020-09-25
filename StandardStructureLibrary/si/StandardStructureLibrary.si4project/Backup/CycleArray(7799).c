#include "./base_types/nodes/wrap.h"
#include "./base_types/nodes/base/public.h"
#include "./base_types/Array.h"
#include <assert.h>


typedef struct 
{
    uint16 pfront;
    uint16 prear;
    pArray parray;
    uint32 length;
} CycleArray_t;

typedef CycleArray_t*   pCycleArray;

/*****************************************************************************
*   Prototype    : cycle_array_create
*   Description  : create a cycle array 
*   Input        : uint32 elem_size
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
pCycleArray cycle_array_create(uint32 elem_size,bool (* freefunc)(void * elem)  )
{
    pCycleArray pCArray = (pCycleArray)Malloc(sizeof(CycleArray_t));

    pCArray->length = 0;
    pCArray->parray = pCArray->prear = 0;
    //the init alloc elems num = 8  so the memery size is  8 * elem_size
    pCArray->parray = array_create(elem_size, freefunc);
    
    assert(pCArray->parray != NULL);
}

/*****************************************************************************
*   Prototype    : cycle_array_destory
*   Description  : destory a cycle array
*   Input        : pCycleArray pCarray
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
bool cycle_array_destory( pCycleArray pCarray )
{
    array_destory(pCarray->parray);
    pCarray->parray = NULL;
    memset(pCarray,0,sizeof(CycleArray_t));
    return TRUE;
}


/*****************************************************************************
*   Prototype    : cycle_array_add
*   Description  : add a elems into cycle array 
*   Input        : pCycleArray pCArray
*                  const void* resource
*                  uint32 i_elem_size
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/26
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_array_add(pCycleArray pCArray,const void* resource, uint32 i_elem_size )
{
   if(cycle_array_full(pCArray))
   {
      pCArray->prear = (pCArray->prear + 1) % pCArray->parray->alloc_num;
   }
   bool ret = array_add(pCArray->parray, pCArray->prear, resource, i_elem_size);
   //prear is the index of parray`s elem
   pCArray->prear +=1; 
   pCArray->length ++; 
   return ret;     
}

/*****************************************************************************
*   Prototype    : cycle_array_del
*   Description  : del a elem from cycleArray by index
*   Input        : pCycleArray pCarray
*                  uint32 index
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/26
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_array_del( pCycleArray pCarray, uint32 index )
{
    bool ret = array_del(pCarray->parray, index);
    pCarray->length --;
    void* dest = array_get(pCarray->parray, index);
    return ret;
}

/*****************************************************************************
*   Prototype    : cycle_array_empty
*   Description  : Make sure the array is empty
*   Input        : pCycleArray pCarray
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/26
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_array_empty( pCycleArray pCarray )
{
    return pCarray->prear == pCarray->pfront;
}

/*****************************************************************************
*   Prototype    : cycle_array_full
*   Description  : make suer the array is full
*   Input        : pCycleArray pCarray
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/26
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_array_full( pCycleArray pCarray )
{
    return (pCarray->prear + 1) % pCarray->parray->alloc_num == pCarray->pfront;
}








