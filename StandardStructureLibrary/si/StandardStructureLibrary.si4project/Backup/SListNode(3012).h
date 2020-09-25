/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : SListNode.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/2
*  Last Modified :
*  Description   : SListNode.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/2
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __SLISTNODE_H__
#define __SLISTNODE_H__


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

extern int compare2( p_list_node one, p_list_node two );
extern bool emptyListNode( p_list_node p_l_node );
extern void setListNode(p_list_node p_l_node, pNode data);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SLISTNODE_H__ */
