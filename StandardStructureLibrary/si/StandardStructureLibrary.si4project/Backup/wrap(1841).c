#include "./wrap.h"

/*****************************************************************************
*   Prototype    : perror_usr_exit
*   Description  : perror with user string
*   Input        : const char* str  
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/8/4
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void perror_usr_exit( const char* str )
{
    D_TRACE(str);
    exit(-1);
}



/*****************************************************************************
*   Prototype    : Malloc
*   Description  : system malloc with error check and bzero
*   Input        : unsigned int size
*   Output       : None
*   Return Value : void*
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/8/5
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void* Malloc( unsigned int size )
{
    void* temp = malloc(size);
    if(NULL == temp)
    {
        D_TRACE("malloc a new node error:");        
        return NULL;
    }
    memset(temp,0,size);
    D_TRACE("Malloc a memery %d  the mem place %p\n",size,temp);
    return temp;
}


/*****************************************************************************
*   Prototype    : getIncNum
*   Description  : get a range size the increase number
*   Input        : unsigned int size
*   Output       : None
*   Return Value : unsigned int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/8
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
unsigned int getIncNum(unsigned int size )
{
    static unsigned int num_count = 0;
    if(num_count <= size)
    {
        return ++num_count;
    }
    else if(num_count > size)
    {
        num_count = 0;
    }
}

/*****************************************************************************
*   Prototype    : Realloc
*   Description  : system realloc with the memset
*   Input        : void *mem_address
*                  unsigned int newsize
*   Output       : None
*   Return Value : void *
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
void* Realloc( void *mem_address, unsigned int newsize )
{
    return realloc(mem_address,newsize);
}