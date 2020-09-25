/******************************************************************************
*
*  Copyright (C), 2015-2025, mengxing Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : BinaryTree.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/6/18
*  Last Modified :
*  Description   : BinaryTree.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/6/18
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern pBTree bTree_create();
extern bool bTree_destory( pBTree tree );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __BINARYTREE_H__ */
