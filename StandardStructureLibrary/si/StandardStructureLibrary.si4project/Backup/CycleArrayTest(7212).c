#include "./standard_types/CycleArray.h"
#include "./standard_types/base_types/nodes/base/Node.h"
typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;


int main(int argc,char* argv[])
{
    D_TRACE("start main\n");
    pCycleArray pCArray = cycle_array_create(3,sizeof(Node_t),freeNode);

    pTask task = (pTask)Malloc(sizeof(Task_t));
    pTask task2 = (pTask)Malloc(sizeof(Task_t));
    pTask task3 = (pTask)Malloc(sizeof(Task_t));
    task->task_id = 111;
    task2->task_id = 222;
    task3->task_id = 333;
    
    pNode one = getNodeMem(1, sizeof(Task_t), task);
    pNode two = getNodeMem(2, sizeof(Task_t), task2);
    pNode three = getNodeMem(3, sizeof(Task_t), task3);

    //cycle array add 
    cycle_array_add(pCArray, one, sizeof(Node_t));
    cycle_array_add(pCArray, two, sizeof(Node_t));
    cycle_array_add(pCArray, three, sizeof(Node_t));

    cycle_array_destory(pCArray);
    D_TRACE("main destory pCArray suncc\n");    
    return 0;
}


