#include "./standard_types/Stack.h"

typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

bool printItem2(pNode temp)
{
    D_TRACE("print a task data-> %d\n",((pTask)temp->pnode)->task_id);
}

int main(int argc,char* argv[])
{
    
    D_TRACE("start main\n");
    pStack pstack = stack_create(8,sizeof(pNode),freeNode);

    pTask task1 = (pTask)Malloc(sizeof(Task_t));
    pTask task2 = (pTask)Malloc(sizeof(Task_t));
    pTask task3 = (pTask)Malloc(sizeof(Task_t));
    task1->task_id = 16;
    task2->task_id = 32;
    task3->task_id = 64;
    
    pNode one = getNodeMem(1, sizeof(pNode), task1);
    pNode two = getNodeMem(2, sizeof(pNode), task2); 
    pNode three = getNodeMem(3, sizeof(pNode), task3);

    stack_push(pstack, one);
    stack_push(pstack, two);
    stack_push(pstack, three);

    pNode temp = stack_pop(pstack);
    //弹栈出来的指针 必须进行控制必须释放栈内部存放的是 指针   是不会释放的
    printItem2(temp);
    freeNode(temp);
    temp = stack_pop(pstack);
    printItem2(temp);
    freeNode(temp);


    
    stack_destory(pstack);
    return 0;
}


