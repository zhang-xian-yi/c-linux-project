#include "./nodes/BinaryTreeNode.h"
typedef struct _T_Binary_Tree
{
    uint32   node_num;
    pBTNode  root;
}BTree_t;

typedef BTree_t*  pBTree;


/*****************************************************************************
*   Prototype    : bTree_create
*   Description  : get the tree mem create a tree
*   Input        : None
*   Output       : None
*   Return Value : pBTree
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/12
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pBTree bTree_create(  )
{
    pBTree ret = (pBTree)Malloc(sizeof(BTree_t));


    
    return ret;
}

