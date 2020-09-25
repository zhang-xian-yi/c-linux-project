/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : DListNode.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/8
*  Last Modified :
*  Description   : DListNode.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/8
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __DLISTNODE_H__
#define __DLISTNODE_H__


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

extern int compare2( pSListNode one, pSListNode two );
extern bool emptyDListNode( pDListNode i_node );
extern bool equal2DListNode(pDListNode one,pDListNode two);
extern void freeDListNode( pDListNode i_dn );
extern pDListNode getDListNodeMem( uint32 id, uint32 count, pNode pnode );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DLISTNODE_H__ */
