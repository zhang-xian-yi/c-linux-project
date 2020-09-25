#include "./standard_types/FixedArray.h"

typedef struct _T_Task
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

bool freeNodeT( pNode node )
{
    //if the pnode is not empty must free the pointer
    free(node->pnode);
    memset(node,0,sizeof(Node_t));
    return TRUE;
}

int main(int argc,char* argv[])
{
    D_TRACE("start main\n");
    pFixArray pFArray = fix_array_create(3,sizeof(Node_t),freeNodeT);

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

    //cycle array add 
    fix_array_add(pFArray, one, sizeof(Node_t));
    fix_array_add(pFArray, two, sizeof(Node_t));
    fix_array_add(pFArray, three, sizeof(Node_t));
    fix_array_add(pFArray, forth, sizeof(Node_t));
    /*must use the 3 num  can not use three->id  
    because the add operation  ----will free the memery only save the value 
    */
    pNode temp_2 = fix_array_get(pFArray, 3);
    D_TRACE("get the pnode the task id %d \n",((pTask)temp_2->pnode)->task_id);
    
    fix_array_destory(pFArray);
    D_TRACE("main destory pFArray suncc\n");    
    return 0;
}


