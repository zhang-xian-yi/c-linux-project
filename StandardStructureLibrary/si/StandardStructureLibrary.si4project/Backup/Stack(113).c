#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#include "./base_types/nodes/wrap.h"

typedef struct 
{
    int log_length;      //stack elem num
    int alloc_length;    //alloc the memery 
    int elem_size;       //elem size
    void * elems;          //stack space
    void (* freefn)(void *); // free the memery func pointer
} Stack_t;

typedef Stack_t*   pStack;


int main(int argc, char* argv[])
{
    const char *friends[] = {"Alan","Bob","Carl","Frank","Mike"};
    Stack_t stringStack;

    //for string to say，push string address，so the elem length  = sizeof(char*)
    stack_new(&stringStack,sizeof(char*),string_free);
    for(int i=0;i<5;i++)
    {
        char * copy = strdup(friends[i]);  //malloc in heap
        stack_push(&stringStack,&copy);
    }
    char *name;
    for(int i=0;i<5;i++)
    {
        stack_pop(&stringStack,&name);
        printf("%s\n",name);
        free(name);    //因为这块内存是strdup分配的，使用完毕后必须free
    }
    stack_destory(&stringStack);
    const int intarr[] = {1,2,3,4,5,6};
    Stack_t intStack;
    //对int而言，压入栈的是int值本身，因此元素长度为sizeof(int)，且无需freefn
    stack_new(&intStack,sizeof(int),NULL);
    for(int i=0;i<6;i++)
    {
        stack_push(&intStack,(void *)&intarr[i]);
    }
    
    int val;
    for(int i=0;i<6;i++)
    {
        stack_pop(&intStack,&val);
        printf("%d\n",val);
    }
    stack_destory(&intStack);
    return 0;
}

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
void stack_new(pStack  s,int elemsize, void (* freefn)(void *))
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
static void string_free(void * elem)
{
    free(*(char **)elem);
}
