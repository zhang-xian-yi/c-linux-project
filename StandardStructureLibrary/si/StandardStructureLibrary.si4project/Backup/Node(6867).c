#include "./include/Node.h"


/*****************************************************************************
*   Prototype    : equals
*   Description  : compare two nodes is equal
*   Input        : pNode one
*                  pNode two
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/1
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool equals( pNode one, pNode two )
{
    if(one->id == two->id)
    {
        return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
*   Prototype    : compare2
*   Description  : compare two nodes return big or small
*   Input        : pNode one
*                  pNode two
*   Output       : None
*   Return Value : uint8
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/1
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
uint8 compare2( pNode one, pNode two )
{
    if( TRUE == equals(one,two) )
    {
        return EQUAL;
    }
    if(one->id > two->id)
    {
        return BIGGER;
    }
    else if(one->id > two->id)
    {
        return SMALLER;
    }
}

   


