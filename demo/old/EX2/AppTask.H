/*************************************************************************************
** 文件: AppTask.h
** 说明: 用户任务声明
** 作者: Jun
** 时间: 2010-6-26
*************************************************************************************/
#ifndef FAMES_AppTask_H
#define FAMES_AppTask_H


void far TaskMain(void * data);
void far TaskTest(void * data);



#define  pause(ns)  ENTER_CRITICAL(); DELAY(ns); EXIT_CRITICAL();












#endif                                      /* #ifndef FAMES_AppTask_H             */

/*
*本文件结束: AppTask.h ===============================================================
*/

