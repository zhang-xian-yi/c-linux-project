#include "./standard_types/DCycleList.h.h"

typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

bool printItem2(pCycleListNode temp,uint32 node_id)
{
    if(temp->pnext->pdata->id != node_id)
    {
        return FALSE;
    }
    else if(temp->pnext->pdata->id == node_id)
    {
        D_TRACE("print a task data-> %d\n",((pTask)temp->pnext->pdata->pnode)->task_id);
        return TRUE;
    }
}

bool printItemAll(pCycleListNode temp,uint32 u_id)
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
    task->task_id = 111;
    task2->task_id = 222;
    task3->task_id = 333;
    
    pCycleListNode one = getCycleListNodeMem(1, sizeof(Task_t), task);
    pCycleListNode two = getCycleListNodeMem(2, sizeof(Task_t), task2);
    pCycleListNode three = getCycleListNodeMem(3, sizeof(Task_t), task3);
    
    cycle_list_add(plist, one);
    cycle_list_add(plist, two);
    cycle_list_add(plist, three);

    cycle_list_control(plist, printItem2, 3);
    D_TRACE("plist del a list node start\n");    
    cycle_list_del(plist, two);
    D_TRACE("print all list node data  start\n");
    cycle_list_control(plist, printItemAll, 0);
    cycle_list_destory(plist);
    D_TRACE("main destory plist suncc\n");    
    return 0;
}


