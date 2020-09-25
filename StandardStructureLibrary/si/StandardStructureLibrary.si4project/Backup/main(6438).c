#include "./standard_types/base_types/DList.h"

typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

bool printItem2(pDListNode temp,uint32 node_id)
{
    if(temp->pdata->id != node_id)
    {
        return FALSE;
    }
    else if(temp->pdata->id == node_id)
    {
        D_TRACE("print a task data-> %d\n",((pTask)temp->pdata->pnode)->task_id);
        return TRUE;
    }
}

bool printItemAll(pDListNode temp,uint32 u_id)
{
    D_TRACE("print all task data-> %d\n",((pTask)temp->pnext->pdata->pnode)->task_id);
    return FALSE;
}

int main(int argc,char* argv[])
{
    D_TRACE("start main\n");
    pDList plist = dlist_create();

    pTask task = (pTask)Malloc(sizeof(Task_t));
    pTask task2 = (pTask)Malloc(sizeof(Task_t));
    pTask task3 = (pTask)Malloc(sizeof(Task_t));
    task->task_id = 100;
    task2->task_id = 888;
    task3->task_id = 222;
    
    pDListNode one = getDListNodeMem(1, sizeof(Task_t), task);
    pDListNode two = getDListNodeMem(2, sizeof(Task_t), task2);
    pDListNode three = getDListNodeMem(3, sizeof(Task_t), task3);
    
    dlist_add(plist, one);
    dlist_add(plist, two);
    dlist_add(plist, three);

    dlist_control(plist, printItem2, 3);
    D_TRACE("plist del a list node start\n");    
    dlist_delById(plist, two->pdata->id);
    D_TRACE("print all list node data  start\n");
    dlist_control(plist, printItemAll, 0);
    dlist_destory(plist);
    D_TRACE("main destory plist suncc\n");    
    return 0;
}


