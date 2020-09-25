#include "./Stack.h"

/*****************************************************************************
*   Prototype    : stack_new
*   Description  : init the stack
*   Input        : uint32 elem_num               
*                  uint32 elemsize             
*                  void (* freefn)(void *)  
*   Output       : None
*   Return Value : pStack
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/11
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pStack stack_create(uint32 elem_num,uint32 elemsize, void (* freefn)(void *))
{
    pStack s = (pStack)Malloc(sizeof(Stack_t));
    
    s->alloc_length = 8;
    s->elem_num = 0;
    s->elem_size = elemsize;
    s->freefn = freefn;
    s->elems = Malloc( s->alloc_length * s->elem_size );
    assert(s->elems != NULL);
    return s;
}

/*****************************************************************************
*   Prototype    : stack_destory
*   Description  : destory the stack
*   Input        : pStack  pstack  
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/11
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void stack_destory(pStack  pstack)
{
    if(pstack->freefn != NULL) 
    {
        for(int i=0;i<pstack->elem_num;i++)
        {
            pNode elem = pstack->elems + i ;
            pstack->freefn(elem);
        }
    }
    free(pstack->elems);
}

/*****************************************************************************
*   Prototype    : stack_grow
*   Description  : stack grow and realloc
*   Input        : pStack pstack  
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/11
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void stack_grow(pStack pstack)
{
    //grow the stack for 2 times
    pstack->alloc_length *= 2;
    pstack->elems = Realloc(pstack->elems,pstack->alloc_length * pstack->elem_size);
    assert(pstack->elems != NULL);
}

/*****************************************************************************
*   Prototype    : stack_push
*   Description  : push a elem type
*   Input        : pStack pstack    
*                  pNode elemaddr  
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/11
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void stack_push(pStack pstack, pNode elemaddr)
{
    if(pstack->elem_num >= pstack->alloc_length)
    {
        stack_grow(pstack);
    }
    pNode target = pstack->elems + pstack->elem_num;
    memcpy(target,&elemaddr,pstack->elem_size);
    pstack->elem_num ++;
}

/*****************************************************************************
*   Prototype    : stack_pop
*   Description  : pop a stack elem
*   Input        : pStack pstack    
*                  pNode elemaddr  
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/11
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void stack_pop(pStack pstack,pNode  elemaddr)
{
    pstack->elem_num --;
    void * source = pstack->elems + pstack->elem_num ;
    memcpy(elemaddr,source,pstack->elem_size);
}
