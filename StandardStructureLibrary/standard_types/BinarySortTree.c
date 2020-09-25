#include "./base_types/BinaryTree.h"

typedef struct _T_Binary_Sort_Tree
{
    uint32      id;
    pBTree      ptree;
}BST_t;

typedef BST_t*  pBST;

/*****************************************************************************
*   Prototype    : bst_create
*   Description  : create a binary sort tree
*   Input        : None
*   Output       : None
*   Return Value : pBST
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/21
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
pBST bst_create(  )
{   
    pBST ret = (pBST)Malloc(sizeof(BST_t));
    ret->id = 1;
    ret->ptree = NULL;
    return ret;
}



/*****************************************************************************
*   Prototype    : bst_destory
*   Description  : destory a binary sort tree
*   Input        : pBST pbst
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/21
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool bst_destory( pBST pbst )
{
    bTree_destory(pbst->ptree);
    memset(pbst,0,sizeof(BST_t));
    free(pbst);
    return true;
}


/*****************************************************************************
*   Prototype    : bst_add
*   Description  : add a btree into the input pbst
*   Input        : pBST pbst
*                  pBTree tree
*   Output       : None
*   Return Value : bool
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/21
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
bool  bst_add( pBST pbst,pBTree tree )
{
    if(NULL == pbst->ptree)
    {
        pbst->ptree = tree;
    }
    else if(NULL != pbst->ptree)
    {
        bTree_add(pbst->ptree, tree->root);
    }
}










