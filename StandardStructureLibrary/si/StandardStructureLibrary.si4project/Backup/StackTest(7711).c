#include "./standard_types/Stack.h"

typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

bool printItem2(pNode temp,uint32 node_id)
{
    if(temp->id != node_id)
    {
        return FALSE;
    }
    else if(temp->id == node_id)
    {
        D_TRACE("print a task data-> %d\n",((pTask)temp->pdata->pnode)->task_id);
        return TRUE;
    }
}

int main(int argc,char* argv[])
{
    
    D_TRACE("start main\n");
    pStack pstack = stack_create();

    pTask task = (pTask)Malloc(sizeof(Task_t));
    pTask task2 = (pTask)Malloc(sizeof(Task_t));
    pTask task3 = (pTask)Malloc(sizeof(Task_t));
    task->task_id = 111;
    task2->task_id = 222;
    task3->task_id = 333;
    
    pNode  = getNodeMem(1, sizeof(pNode), task1); 
}


