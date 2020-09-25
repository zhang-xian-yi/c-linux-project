#include "./Stack.h"

/*****************************************************************************
*   Prototype    : stack_create
*   Description  : create the stack
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
pStack stack_create(uint32 alloc_num,uint32 elemsize, void (* freefn)(void *))
{
    pStack s = (pStack)Malloc(sizeof(Stack_t));
    
    s->alloc_length = alloc_num;
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
bool stack_destory(pStack  pstack)
{
    if(pstack->freefn != NULL) 
    {
        for(int i=0;i<pstack->elem_num;++i)
        {
            pstack->freefn(pstack->elems[i]);
        }
    }
    free(pstack->elems);
    free(pstack);
    return;
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
pNode stack_pop(pStack pstack)
{
    //static var  only init once
    static pNode source;
    //assign the static var
    source = NULL;
    //get the return pNode 
    pstack->elem_num --;
    source = pstack->elems[pstack->elem_num];
    //bzero it
    pstack->elems[pstack->elem_num] = 0x0;
    //return the pNode;
    return source;
}
