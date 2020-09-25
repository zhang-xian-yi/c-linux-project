#include "./types/SList.h"

typedef struct _T_int
{
    int task_id;
}Task_t;

typedef Task_t* pTask;

void printItem(pSListNode temp)
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
    pNode node =  getNodeMem(1, 1, task);
    pSListNode one = getListNodeMem(node);
    
    pNode node2 =  getNodeMem(2, 1, task2);
    pSListNode two = getListNodeMem(node2);
    
    pNode node3 =  getNodeMem(3, 1, task3);
    pSListNode three = getListNodeMem(node3);
    
    slist_add(plist, one);
    slist_add(plist, two);
    slist_add(plist, three);
    printItem(plist->p_pos);
    printItem(getListNode(plist,2));
    D_TRACE("plist del a list node start\n");    
    slist_del(plist, two);
    slist_destory(plist);
    D_TRACE("main destory plist suncc\n");    
    return 0;
}


