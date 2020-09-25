#include "./Stack.h"

/*****************************************************************************
*   Prototype    : stack_new
*   Description  : init the stack
*   Input        : pStack  s                
*                  int elemsize             
*                  void (* freefn)(void *)  
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
void stack_create(pStack  s,int elemsize, void (* freefn)(void *))
{
    s->alloc_length = 4;
    s->log_length = 0;
    s->elem_size = elemsize;
    s->freefn = freefn;
    s->elems = Malloc(4*elemsize);
    assert(s->elems != NULL);
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
        for(int i=0;i<pstack->log_length;i++)
        {
            void * elem = (char *)pstack->elems + i * pstack->elem_size;
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
    pstack->elems = realloc(pstack->elems,pstack->alloc_length * pstack->elem_size);
    assert(pstack->elems != NULL);
}

/*****************************************************************************
*   Prototype    : stack_push
*   Description  : push a elem type
*   Input        : pStack pstack    
*                  void * elemaddr  
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
void stack_push(pStack pstack,void * elemaddr)
{
    if(pstack->log_length == pstack->alloc_length)
    {
        stack_grow(pstack);
    }
    void * target = (char *)pstack->elems + pstack->log_length * pstack->elem_size;
    memcpy(target,elemaddr,pstack->elem_size);
    pstack->log_length ++;
}

/*****************************************************************************
*   Prototype    : stack_pop
*   Description  : pop a stack elem
*   Input        : pStack pstack    
*                  void * elemaddr  
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
void stack_pop(pStack pstack,void * elemaddr)
{
    pstack->log_length --;
    void * source = (char *)pstack->elems + pstack->log_length * pstack->elem_size;
    memcpy(elemaddr,source,pstack->elem_size);
}

/*****************************************************************************
*   Prototype    : string_free
*   Description  : define a string free func
*   Input        : void * elem  
*   Output       : None
*   Return Value : static void
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
void string_free(void * elem)
{
    free(*(char **)elem);
}
