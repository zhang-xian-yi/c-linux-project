#include "./wrap.h"

num_count = 0;

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
*   Input        : uint32 size
*   Output       : None
*   Return Value : uint32
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
uint32 getIncNum( uint32 size )
{
    if(num_count <= size)
    {
        return num_count++;
    }
    else if(num_count > size)
    {
        num_count = 0;
    }
}