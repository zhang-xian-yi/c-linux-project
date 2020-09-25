#include "./standard_types/base_types/NodeSequence.h"

typedef struct _T_Task
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

int main(int argc,char* argv[])
{
    D_TRACE("start main\n");
    pNSequence pNseq = nSequence_create(4,sizeof(pNode),freeNode);

    pTask task1 = (pTask)Malloc(sizeof(Task_t));
    pTask task2 = (pTask)Malloc(sizeof(Task_t));
    pTask task3 = (pTask)Malloc(sizeof(Task_t));
    pTask task4 = (pTask)Malloc(sizeof(Task_t));
    task1->task_id = 16;
    task2->task_id = 32;
    task3->task_id = 48;
    task4->task_id = 64;
    
    pNode one = getNodeMem(1, sizeof(Task_t), task1);
    pNode two = getNodeMem(2, sizeof(Task_t), task2);
    pNode three = getNodeMem(3, sizeof(Task_t), task3);
    pNode forth = getNodeMem(4, sizeof(Task_t), task4);

    //nSequence add 
    nSequence_add(pNseq, one);
    nSequence_add(pNseq, two);
    nSequence_add(pNseq, three);
    nSequence_add(pNseq, forth);
   
    pNode temp_2 = nSequence_get(pNseq, 3);
    D_TRACE("get the pnode the task id %d \n",((pTask)temp_2->pnode)->task_id);
    nSequence_del(pNseq, temp_2->id);

    nSequence_grow(pNseq);
    pTask task5 = (pTask)Malloc(sizeof(Task_t));
    pTask task6 = (pTask)Malloc(sizeof(Task_t));
    task5->task_id = 128;
    task6->task_id = 256;
    pNode five = getNodeMem(5, sizeof(Task_t), task5);
    pNode six = getNodeMem(6, sizeof(Task_t), task6);
    nSequence_add(pNseq, five);
    nSequence_add(pNseq, six);

    pNode temp_6 = nSequence_get(pNseq, 6);
    D_TRACE("add new node get  value =  %d \n",((pTask)temp_6->pnode)->task_id);
    
    nSequence_destory(pNseq);
    D_TRACE("main destory pFArray suncc\n");    
    return 0;
}


