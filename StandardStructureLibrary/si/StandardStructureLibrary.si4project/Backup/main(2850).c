#include "./standard_types/SQueue.h"

typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;


bool printItem2(pQueueNode temp,uint32 node_id)
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

bool printItemAll(pQueueNode temp,uint32 u_id)
{
    D_TRACE("print all task data-> %d\n",((pTask)temp->pnext->pdata->pnode)->task_id);
    return FALSE;
}

void printItem(pQueueNode node)
{
    D_TRACE("print one task data-> %d\n",((pTask)node->pdata->pnode)->task_id);
}

int main(int argc,char* argv[])
{
    D_TRACE("start main\n");
    pQueue pqueue = squeue_create();

    pTask task = (pTask)Malloc(sizeof(Task_t));
    pTask task2 = (pTask)Malloc(sizeof(Task_t));
    pTask task3 = (pTask)Malloc(sizeof(Task_t));
    task->task_id = 111;
    task2->task_id = 222;
    task3->task_id = 333;
    
    pQueueNode one = getQueueNodeMem(1, 1, task);
    pQueueNode two = getQueueNodeMem(2, 1, task2);
    pQueueNode three = getQueueNodeMem(3, 1, task3);
    
    squeue_add(pqueue, one);
    squeue_add(pqueue, two);
    squeue_add(pqueue, three);

    squeue_control(pqueue, printItem2, 3);
    D_TRACE("plist del a list node start\n");    
    pQueueNode node = squeue_pop(pqueue);
    D_TRACE("print pop node start\n");    
    printItem(node);
    freeSListNode(node);
    D_TRACE("print all list node data  start\n");
    squeue_control(pqueue, printItemAll, 0);
    squeue_destory(pqueue);
    D_TRACE("main destory plist suncc\n");    
    return 0;
}


