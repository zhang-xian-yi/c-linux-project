/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : Array.c
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/20
*  Last Modified :
*  Description   : array.c file implments all base function
*  Function List :
*
*       1.                array_create
*       2.                array_destory
*       3.                array_get
*       4.                array_grow
*       5.                array_set
*
*  History:
* 
*       1.  Date         : 2020/5/20
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#include "./Array.h"




/*****************************************************************************
*   Prototype    : array_create
*   Description  : create a array
*   Input        : uint32 elem_size
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
pArray array_create( uint32 elem_size,bool (*freefunc)(void* elem) )
{
    pArray array = (pArray)Malloc(sizeof(Array_t));

    array->elem_num = 0;
    array->elem_size = elem_size;
    //init  set the array have a 8 num elem size memery
    array->alloc_num = 8;
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
        }
    }
    //realse the parray->elems
    free(parray->elems);
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
        void* dest = array->elems+index * array->elem_size;
        //the elems save the object pointer so *dest == object pointer
        if( NULL != *dest)
        {
            array->freefn(dest);
        }
        memcpy(dest,elem,elem_size);
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



