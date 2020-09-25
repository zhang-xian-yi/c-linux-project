#include "./types/SList.h"

typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

void printItem(pSListNode temp)
{
    D_TRACE("main data-> %d\n",((pTask)(temp->pdata->pnode))->task_id);
}

int main(int argc,char* argv[])
{
    D_TRACE("start main\n");
    pSList plist = slist_create(5);

    pTask task = (pTask)Malloc(sizeof(Task_t));
    task->task_id = 100;
    pNode node =  getNodeMem(1, 1, task);
    pSListNode one = getListNodeMem(node);
    
    slist_add(plist, pSListNode node);
    printItem(plist->p_pos);
    slist_destory(plist);
    D_TRACE("destory plist suncc\n");    
    return 0;
}


