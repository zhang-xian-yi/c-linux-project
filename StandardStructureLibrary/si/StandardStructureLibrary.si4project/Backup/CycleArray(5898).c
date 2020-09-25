/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : CycleArray.c
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/26
*  Last Modified :
*  Description   : The fixed-length loop array provides only the add operat-
                   ion, not the delete
*  Function List :
*
*       1.                cycle_array_add
*       2.                cycle_array_create
*       3.                cycle_array_destory
*       4.                cycle_array_empty
*       5.                cycle_array_full
*
*  History:
* 
*       1.  Date         : 2020/5/26
*           Author       : zhangxianyi
*           Modification : Created file
*/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./base_types/Array.h"
#include <assert.h>


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_CycleArray
{
    uint16 front;
    uint16 rear;
    pArray parray;
}CycleArray_t;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

/******************************************************************************/





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

    pCArray->front = pCArray->rear = 0;
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
      pCArray->front = (pCArray->front + 1) % pCArray->parray->alloc_num;
   }
   bool ret = array_add(pCArray->parray, pCArray->rear, resource, i_elem_size);
   //prear is the index of parray`s elem
   pCArray->rear = (pCArray->rear + 1) % pCArray->parray->alloc_num;
   
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
    return pCarray->rear == pCarray->front;
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
    return (pCarray->rear + 1) % pCarray->parray->alloc_num == pCarray->front;
}








