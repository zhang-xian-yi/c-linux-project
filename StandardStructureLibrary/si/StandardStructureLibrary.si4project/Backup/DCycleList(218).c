#include "./base_types/nodes/DListNode.h"
#include "./base_types/nodes/wrap.h"
#include "./base_types/nodes/base/public.h"


typedef pDListNode    pCycleListNode;
typedef DListNode_t   CycleListNode_t;

typedef bool (*cycle_list_func_oper)(pCycleListNode temp,uint32 nid);

typedef struct _T_DCycleList
{
	uint32              list_length;
	pCycleListNode      phead;
    pCycleListNode      ptail;
}DCycleList_t;

typedef DCycleList_t* pCycleList;


/*****************************************************************************
*   Prototype    : cycle_list_create
*   Description  : create a cycle list
*   Input        : void
*   Output       : None
*   Return Value : pCycleList
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/13
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pCycleList cycle_list_create( void )
{
    pCycleList  plist = (pCycleList)Malloc(sizeof(CycleListNode_t));
    pCycleListNode  header = (pCycleListNode)Malloc(sizeof(CycleListNode_t));
    plist->list_length = 0;
    plist->phead = header;
    plist->ptail = header;
    return plist;
}

/*****************************************************************************
*   Prototype    : cycle_list_destory
*   Description  : destory a cycle list and free it
*   Input        : pCycleList
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/13
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_list_destory( pCycleList  plist)
{
    
}


/*****************************************************************************
*   Prototype    : cycle_list_control
*   Description  : control the cycle list
*   Input        : pCycleList plist
*                  cycle_list_func_oper func
*                  uint32 nid
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/5/13
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool cycle_list_control( pCycleList plist, cycle_list_func_oper func ,uint32 nid)
{
    
}

