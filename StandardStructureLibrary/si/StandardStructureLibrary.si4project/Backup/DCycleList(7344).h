/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : DCycleList.h
*  Version       : Initial Draft
*  Author        : zhangxianyi
*  Created       : 2020/5/16
*  Last Modified :
*  Description   : DCycleList.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/5/16
*           Author       : zhangxianyi
*           Modification : Created file
*
******************************************************************************/
#ifndef __DCYCLELIST_H__
#define __DCYCLELIST_H__


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

extern bool cycle_list_add( pCycleList plist, uint32 list_length,pCycleListNode node );
extern bool cycle_list_control( pCycleList plist, cycle_list_func_oper func ,uint32 nid);
extern pCycleList cycle_list_create( void );
extern bool cycle_list_del( pCycleList plist, pCycleListNode del_node );
extern bool cycle_list_destory( pCycleList  plist);
extern bool cycle_list_empty( pCycleList plist );
extern bool cycle_list_full( pCycleList plist,uint32 list_length );
extern bool equal2CycleListNode( pCycleListNode one, pCycleListNode two );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DCYCLELIST_H__ */
