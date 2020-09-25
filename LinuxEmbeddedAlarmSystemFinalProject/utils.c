#include "utils.h"

/*****************************************************************************
*   Prototype    : Malloc
*   Description  : system malloc with error check
*   Input        : size_t size
*   Output       : None
*   Return Value : void*
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/11/16
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
void* Malloc( size_t size )
{
    void* temp = malloc(size);
    if (NULL == temp) 
    {        
        TRACE("malloc memery error\n");
        return NULL;
    }
    return temp;
}
