/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : FixedArray.c
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/26
*  Last Modified :
*  Description   : The fixed-length loop array provides only the add operat-
                   ion, not the delete
*  Function List :
*
*       1.                fix_array_add
*       2.                fix_array_create
*       3.                fix_array_destory
*       4.                fix_array_empty
*       5.                fix_array_full
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
#include "./FixedArray.h"


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct _T_FixArray
{
    uint16 front;
    uint16 rear;
    pArray parray;
}FixArray_t ;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

/******************************************************************************/





/*****************************************************************************
*   Prototype    : fix_array_create
*   Description  : create a fixed len array 
*   Input        : uint32 length
*                  uint32 elem_size
*                  void (* freefunc)(void *)
*
*   Output       : None
*   Return Value : pFixArray
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
pFixArray fix_array_create(uint32 length,uint32 elem_size,bool (* freefunc)(void * elem)  )
{
    pFixArray pFArray = (pFixArray)Malloc(sizeof(FixArray_t));
    pFArray->front = pFArray->rear = 0;
    //the init alloc elems num = 8  so the memery size is  8 * elem_size
    pFArray->parray = array_create(length,elem_size, freefunc);
    
    assert(pFArray->parray != NULL);
    D_TRACE("cycle array create succ\n");
    return pFArray;
}

/*****************************************************************************
*   Prototype    : fix_array_destory
*   Description  : destory a fixed len array
*   Input        : pFixArray pCarray
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
bool fix_array_destory( pFixArray pFarray )
{
    array_destory(pFarray->parray);
    memset(pFarray,0,sizeof(FixArray_t));
    free(pFarray);
    pFarray = NULL;
    D_TRACE("cycle array destory succ\n");
    return TRUE;
}


/*****************************************************************************
*   Prototype    : fix_array_add
*   Description  : add a elems into fixed len array 
*   Input        : pFixArray pCArray
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
bool fix_array_add(pFixArray pFarray,const void* resource, uint32 i_elem_size )
{
   if(fix_array_full(pFarray))
   {
      pFarray->front = (pFarray->front + 1) % ((pFarray->parray)->alloc_num);
   }
   bool ret = array_add(pFarray->parray, pFarray->rear, resource, i_elem_size);
   //prear is the index of parray`s elem
   pFarray->rear = (pFarray->rear + 1) % (pFarray->parray->alloc_num);
   D_TRACE("cycle array add \n");
   return ret;     
}


/*****************************************************************************
*   Prototype    : fix_array_empty
*   Description  : Make sure the fixed len array is empty
*   Input        : pFixArray pCarray
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
bool fix_array_empty( pFixArray pCarray )
{
    return pCarray->rear == pCarray->front;
}

/*****************************************************************************
*   Prototype    : fix_array_full
*   Description  : make suer the fixed len array is full
*   Input        : pFixArray pCarray
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
bool fix_array_full( pFixArray pCarray )
{
    return (pCarray->rear + 1) % pCarray->parray->alloc_num == pCarray->front;
}

/*****************************************************************************
*   Prototype    : fix_array_get
*   Description  : get a node from pFarray by node id
*   Input        : pFixArray pFArray  
*                  uint32 nid         
*   Output       : None
*   Return Value : pNode
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/27
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pNode fix_array_get(pFixArray pFArray,uint32 nid)
{
    Node_t temp;
    setNode(&temp, nid, 0, NULL);
    for(int i = pFArray->front ; i != pFArray->rear;)
    {
        void* dest_addr = pFArray->parray->elems + i * pFArray->parray->elem_size;
        if(equals2Node(&temp, dest_addr))
        {
            return dest_addr;
        }
        //prevent more than the memery border
        i = (i + 1) % pFArray->parray->alloc_num ;
    }
    return NULL;
}









