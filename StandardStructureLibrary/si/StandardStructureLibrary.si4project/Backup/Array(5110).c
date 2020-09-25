/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : Array.c
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/26
*  Last Modified :
*  Description   : array.c file implments all base function
*  Function List :
*
*       1.                array_add
*       2.                array_create
*       3.                array_del
*       4.                array_destory
*       5.                array_get
*       6.                array_grow
*       7.                array_set
*
*  History:
* 
*       1.  Date         : 2020/5/26
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <assert.h>
#include "./Array.h"


/*****************************************************************************
*   Prototype    : array_create
*   Description  : create a array
*   Input        : uint32 length
*                  uint32 elem_size
*                  (*freefunc)(void* elem)
*   Output       : None
*   Return Value : pArray
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/20
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pArray array_create(uint32 length, uint32 elem_size,bool (*freefunc)(void* elem) )
{
    pArray array = (pArray)Malloc(sizeof(Array_t));

    array->elem_num = 0;
    array->elem_size = elem_size;
    //init  set the array have a length num elem size memery
    array->alloc_num = length;
    array->freefn = freefunc;
    
    array->elems = Malloc(array->alloc_num * array->elem_size);
    assert(array->elems);
    return array;
}

/*****************************************************************************
*   Prototype    : array_destory
*   Description  : destory a array
*   Input        : pArray parray
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/20
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool array_destory( pArray parray )
{
    if(NULL != parray->freefn)
    {
        //free the elem nums count  object
        for(int i = 0;i < parray->elem_num ;++i)
        {
            void* elem_addr = parray->elems + i * parray->elem_size;
            parray->freefn(elem_addr);
            parray->elems = elem_addr;
        }
    }
    //realse the parray->elems
    //free(parray->elems);
    memset(parray,0,sizeof(Array_t));
    return TRUE;
}

/*****************************************************************************
*   Prototype    : array_get
*   Description  : get a object from array by index 
*   Input        : pArray array
*                  uint32 index
*   Output       : None
*   Return Value : void* 
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/20
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void*  array_get(pArray array, uint32 index )
{
    return array->elems + index * array->elem_size;
}

/*****************************************************************************
*   Prototype    : array_set
*   Description  : set a object at array by index
*   Input        : pArray array
*                  uint32 index
*                  void* elem
*                  uint32 elem_size
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/20
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool array_set( pArray array, uint32 index, void* elem, uint32 elem_size )
{
    bool ret = FALSE;
    //confirm the similar data type 
    if(elem_size == array->elem_size)
    {
        void* dest = array->elems + index * array->elem_size;
        //the elems save the object pointer so *dest == object pointer
        if( TRUE != isEmptyNode(dest))
        {
            array->freefn(dest);
            array->elem_num -- ;
        }
        //the array only save pointer   how to save pointer??????
        memcpy(dest,elem,array->elem_size);
    }
    return TRUE;
}

/*****************************************************************************
*   Prototype    : array_grow
*   Description  : if the num more then alloc num so grow the array memery
                   size
*   Input        : pArray array
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/20
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool array_grow( pArray parray )
{
    //grow the array for 2 times
    parray->alloc_num *= 2;
    parray->elems = Realloc(parray->elems,parray->alloc_num * parray->elem_size);
    assert(parray->elems != NULL);
}

/*****************************************************************************
*   Prototype    : array_add
*   Description  : add a elem into array by index
*   Input        : pArray parray
*                  uint32 index
*                  void* resource
*                  uint32 src_size
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
bool array_add( pArray parray, uint32 index, void* resource, uint32 src_size )
{
    bool ret = FALSE;
    ret = array_set(parray, index, resource, src_size);
    if(parray->elem_num < parray->alloc_num)
    {
        parray->elem_num++;
    }
    return ret;
}

/*****************************************************************************
*   Prototype    : array_del
*   Description  : del a elem from array by index 
*   Input        : pArray parray
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
bool array_del( pArray parray, uint32 index )
{
    void* del_elem = array_get( parray,  index);
    bool ret = FALSE;
    if(NULL != del_elem)
    {
        ret = parray->freefn(del_elem);
    }
    memset(del_elem,0,parray->elem_size);
    parray->elem_num -- ;
    return ret;
}


