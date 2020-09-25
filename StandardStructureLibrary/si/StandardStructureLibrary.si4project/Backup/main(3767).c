#include "./types/SList.h"

typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

bool printItem2(pSListNode temp,uint32 node_id)
{
    if(temp->pnext->pdata->id != node_id)
    {
        return FALSE;
    }
    else if(temp->pnext->pdata->id == node_id)
    {
        D_TRACE("main data-> %d\n",((pTask)temp->pdata->pnode)->task_id);
    }
}

bool printItemAll(pSListNode temp,uint32 u_id)
{
    D_TRACE("main data-> %d\n",((pTask)temp->pdata->pnode)->task_id);
}

int main(int argc,char* argv[])
{
    D_TRACE("start main\n");
    pSList plist = slist_create(5);

    pTask task = (pTask)Malloc(sizeof(Task_t));
    pTask task2 = (pTask)Malloc(sizeof(Task_t));
    pTask task3 = (pTask)Malloc(sizeof(Task_t));
    task->task_id = 100;
    task2->task_id = 888;
    task3->task_id = 222;
    
    pSListNode one = getSListNodeMem2(1, 1, task);
    pSListNode two = getSListNodeMem2(2, 1, task2);
    pSListNode three = getSListNodeMem2(3, 1, task3);
    
    slist_add(plist, one);
    slist_add(plist, two);
    slist_add(plist, three);

    slist_control(plist, printItem2, 3);
    D_TRACE("print all list node data  start\n");  
    slist_control(plist, printItemAll, 0);
    D_TRACE("plist del a list node start\n");    
    slist_del(plist, two);
    slist_control(plist, printItemAll, 0);
    slist_destory(plist);
    D_TRACE("main destory plist suncc\n");    
    return 0;
}


