#include "./nodes/DListNode.h"

typedef struct _T_LinkList
{
    pDListNode                phead;
    pDListNode                p_pos;
    uint32                    list_length;
}DList_t;

typedef DList_t*   pDList;




