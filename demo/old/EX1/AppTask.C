/*************************************************************************************
** 文件: AppTask.C
** 说明: 用户任务定义
** 作者: Jun
** 时间: 2010-6-26
*************************************************************************************/
#define  FAMES_AppTask_C
#include "includes.h"

/*lint -e830 -e768 -e755 -e757 -e756 -e750 -e714 -e526 -e677 -w3 -wlib(0)*/


MutexCB  mutex_testkey;

INT16U testkey(void)
{
    INT16U key=0;

    if(bioskey(1)){
        key=bioskey(0);
        if(key==0)key=bioskey(0);
        if(key&0xff)key&=0xff;
    }

    return key;
}

void prt_string(int x, int y, char * s, char color)
{
    int    i;
    char far * disp=MK_FP(0xb800,0);

    x--,y--;
    (INT32U)disp+=(160L*(long)y+(long)x*2L);
    i=0;
    while(s[i]){
        *disp=s[i];
        disp++;
        *disp=((color==0)?((char)(y%10+4)):color);
        disp++;
        i++;
    }
}


char * uint2string(char * dst, INT16U data)
{
    int  i;
    
    for(i=3; i>=0; i--){
        dst[i]=HEXCHAR[(data)&0xf];
        data>>=4;
    }
    dst[4]=0;
    return dst;
}

char * ulong2string(char * dst, INT32U data)
{
    int  i;
    
    for(i=7; i>=0; i--){
        dst[i]=HEXCHAR[(data)&0xfL];
        data>>=4L;
    }
    dst[8]=0;
    return dst;
}

char * decimal2string(char * dst, INT16U data)
{
    int  i;
    
    for(i=5; i>=0; i--){
        dst[i]=HEXCHAR[(data)%10];
        data/=10;
    }
    dst[6]=0;
    return dst;
}

char * decimal2string3(char * dst, INT16U data)
{
    int  i;
    
    for(i=2; i>=0; i--){
        dst[i]=HEXCHAR[(data)%10];
        data/=10;
    }
    dst[3]=0;
    if(dst[0]=='0'){
        dst[0]=' ';
        if(dst[1]=='0')
            dst[1]=' ';
    }
    return dst;
}


char * uint2char(char * dst, INT16U data)
{
    int  i;

    dst[0]=HEXCHAR[data&0xf];
    dst[1]=0;
    return dst;
}

char * char2str(char * dst, char c)
{
	dst[0]=c;
	dst[1]=0;
	return dst;
}

#define  CHG_OPT_RAW      0x0100
#define  CHG_OPT_DEC      0x0200
#define  CHG_OPT_SIG      0x0400
#define  CHG_OPT_FIL      0x0800
#define  CHG_OPT_ZER      0x1000
#define  CHG_OPT_LFT      0x2000
#define  CHG_OPT_UPR      0x4000
#define  CHG_OPT_LOW      0x8000

/*------------------------------------------------------------------------------------
*   将一个INT8转化为字符串
**----------------------------------------------------------------------------------*/
INT8S * INT8toSTR(INT8S * dst, INT8S src, INT16U opt)
{
	
}

/*------------------------------------------------------------------------------------
*   将一个INT16转化为字符串
**----------------------------------------------------------------------------------*/
INT8S * INT16toSTR(INT8S * dst, INT16S src, INT16U opt)
{
}

/*------------------------------------------------------------------------------------
*   将一个INT32转化为字符串
**----------------------------------------------------------------------------------*/
INT8S * INT32toSTR(INT8S * dst, INT32S src, INT16U opt)
{
}

/*------------------------------------------------------------------------------------
*   字符串转化为字符串
**----------------------------------------------------------------------------------*/
INT8S * STRtoSTR(INT8S * dst, INT8S * src, INT16U opt)
{
}

/*------------------------------------------------------------------------------------
*   取系统的时间日期
**----------------------------------------------------------------------------------*/
void GetDateTime (char *s)
{
    struct time now;
    struct date today;

    gettime(&now);
    getdate(&today);
    sprintf(s, "%02d-%02d-%02d  %02d:%02d:%02d",
               today.da_mon,
               today.da_day,
               today.da_year,
               now.ti_hour,
               now.ti_min,
               now.ti_sec);
}

void dpc_for_test(void * d)
{
    static INT16U i=0;
    INT8S  ts[10];

    prt_string(15, 8, "[", 0);
    prt_string(16, 8, decimal2string(ts, i), 0);
    prt_string(24, 8, "]", 0);
    i++;
}

/*------------------------------------------------------------------------------------
* 函数: TaskMain()
* 说明: 主任务
**----------------------------------------------------------------------------------*/
void far TaskMain(void * data)
{
    INT8S  ts[10];
    INT16U key;
    InitStat();
    TimerInit();
    DispatchLock();
    TaskCreate(TaskTest, (void*)12,  "Task4", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)12,  "Task5", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)11,  "Task6", 512u, 9u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)15,  "Task7", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)13,  "Task8", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)3,   "Task9", 512u, 1u, TASK_CREATE_OPT_NONE);
    DispatchUnlock();
    TimerSet(Timer_for_test, 10L, TIMER_TYPE_AUTO, dpc_for_test, NULL);
    while(1){
        switch(key=testkey()){
            case 0x1b:
                clrscr();
                ExitApplication();
            case 0x4: /*Ctrl-D*/
                TaskDelete(CurrentTask);
                break;
            case 0x13:
                if(!TaskDelete(TaskStatHandle)){
                }
                break;
            case 0x3:
                TaskCreate(TaskStat, NULL, "#STAT", 1024, TaskStatPrio, TASK_CREATE_OPT_NONE);
                break;
            default:
                break;
        }
        if(key){
            prt_string(15, 6, "[", 0);
            prt_string(16, 6, uint2string(ts,key), 0);
            prt_string(20, 6, ", ", 0);
            prt_string(22, 6, ((key&0xff)?char2str(ts, key):" "), 0);
            prt_string(24, 6, "]", 0);
        }

        prt_string(2,    20, "CurrentTask: ", 0);
        prt_string(2+15, 20, uint2char(ts, CurrentTask), 0);
        prt_string(2+19, 20, CurrentTCB->TaskName, 0);
        prt_string(2,    22, "Switches:    [", 0);
        prt_string(16,  22, ulong2string(ts, TaskSwitches), 3);
        prt_string(24,   22, "]  Tasks: ", 0);
        prt_string(34,   22, decimal2string3(ts, NumberOfTasks), 0);
        prt_string(44,   22, "CPU: ", 0);
        prt_string(49,   22, decimal2string3(ts, CPU_USED), 0);
        prt_string(52,   22, "%", 0);
        TaskSleep(10L);
    }
}

/*------------------------------------------------------------------------------------
* 函数: TaskTest()
* 说明: 测试任务
**----------------------------------------------------------------------------------*/
void far TaskTest(void * data)
{
    INT16S tdata;
    INT32U runs=0;
    BOOL   ddddd=NO;
    INT8S  ts[16];
    INT16S namey=2, statey=12;
    INT16S readyy=40, sleepy=60;
    PRIOMAP_TYPE tpt;
    TCB * ptcb;
    INT16S i,j,k;
    static INT16S clrscr_flag=1;

    tdata=(INT16S)data;
    tdata+=1;

    ENTER_CRITICAL();
    if(clrscr_flag){
        clrscr();
        clrscr_flag=0;
    }
    EXIT_CRITICAL();
    
    for(;;){
        runs++;
        
        for(i=0; i<MAX_TASKS; i++){
            prt_string(namey,   2+i*2, TCBS[i].TaskName, 0);
            prt_string(namey+6, 2+i*2, "(", 0);
            prt_string(namey+7, 2+i*2, uint2char(ts, TCBS[i].Priority), 0);
            prt_string(namey+8, 2+i*2, ")", 0);
            prt_string(statey,  2+i*2, uint2char(ts, TCBS[i].TaskState), TCBS[i].TaskState?8:14);
            prt_string(namey+25, 2+i*2, "T=", 0);
            prt_string(namey+27,2+i*2, ulong2string(ts, TCBS[i].TaskTimer), TCBS[i].TaskTimer?14:8);            
        }
        prt_string(namey+13, 2+CurrentTask*2, "[", 0);
        prt_string(namey+14, 2+CurrentTask*2, decimal2string(ts, runs), 0);
        prt_string(namey+22, 2+CurrentTask*2, "]", 0);

        prt_string(readyy,    2, "READYLIST:", 0);
        tpt=READYLIST.PrioMap;
        prt_string(readyy+11, 2, uint2string(ts, tpt), 0);
        for(i=0; i<MAX_PRIORITY; i++){
            prt_string(readyy,   4+i, uint2char(ts, i), 0);
            prt_string(readyy+1, 4+i, ":", 0);            
            prt_string(readyy+3, 4+i, uint2char(ts, tpt&0x1),  (tpt&0x1)?14:8);
            tpt>>=1;
            ptcb=READYLIST.PrioTCBS[i].head;
            prt_string(readyy+6, 4+i, "---------", 0);
            k=0;
            while(ptcb){
                for(j=0; j<MAX_TASKS; j++){
                    if(ptcb == &TCBS[j]){
                        prt_string(readyy+6+k++, 4+i, uint2char(ts, j), 0);
                    }
                }
                ptcb=ptcb->Next;
            }
        }

        prt_string(sleepy,    2, "SLEEPLIST:", 0);
        tpt=SLEEPLIST.PrioMap;
        prt_string(sleepy+11, 2, uint2string(ts, tpt), 0);
        for(i=0; i<MAX_PRIORITY; i++){
            prt_string(sleepy,   4+i, uint2char(ts, i), 0);
            prt_string(sleepy+1, 4+i, ":", 0);            
            prt_string(sleepy+3, 4+i, uint2char(ts, tpt&0x1),  (tpt&0x1)?14:8);
            tpt>>=1;
            ptcb=SLEEPLIST.PrioTCBS[i].head;
            prt_string(sleepy+6, 4+i, "---------", 0);
            k=0;
            while(ptcb){
                for(j=0; j<MAX_TASKS; j++){
                    if(ptcb == &TCBS[j]){
                        prt_string(sleepy+6+k++, 4+i, uint2char(ts, j), 0);
                    }
                }
                ptcb=ptcb->Next;
            }
        }
        prt_string(namey+13, 2, "[", 0);
        prt_string(namey+14, 2, ulong2string(ts, TaskIdleCnts), 0);
        prt_string(namey+22, 2, "]", 0);

        prt_string(namey+13, 4, "[", 0);
        prt_string(namey+14, 4, ulong2string(ts, TaskIdleCtMx), 0);
        prt_string(namey+22, 4, "]", 0);
        
        prt_string(2, 19, "------------------------------------------------------------------------------", 0);
        prt_string(namey,    20, "CurrentTask: ", 0);
        prt_string(namey+15, 20, uint2char(ts, CurrentTask), 0);
        prt_string(namey+19, 20, CurrentTCB->TaskName, 0);
        prt_string(34,       20, ">>>MAX_TASKS=", 0);
        prt_string(47,       20, decimal2string3(ts, MAX_TASKS), 0);
        prt_string(51,       20, ", MAX_PRIORITY=", 0);
        prt_string(66,       20, decimal2string3(ts, MAX_PRIORITY), 0);
        prt_string(2, 21, "------------------------------------------------------------------------------", 0);

        prt_string(2, 24, "Demonstration of Task-Dispatches & TaskList-Movements --- Jun(FamesOS-", 0);
        prt_string(72,24, VersionString")", 0);
        prt_string(2, 25, "------------------------------------------------------------------------------", 0);

        TaskSleep(tdata);
    }
}

/*------------------------------------------------------------------------------------
* 函数: TaskSwitchHook()
* 说明: 任务切换钩子
* 特别: 此函数运行在中断服务程序之中,应特别注意其执行效率
**----------------------------------------------------------------------------------*/
void APICAL TaskSwitchHook(void)
{
}

/*------------------------------------------------------------------------------------
* 函数: InitApplication()
* 说明: 初始化应用程序, 在InitFamesOS()中调用
**----------------------------------------------------------------------------------*/
void APICAL InitApplication(void)
{
    CALLED_ONLY_ONCE();
    MutexInit(&mutex_testkey);
    TaskCreate(TaskMain, (void*)0, "Task2", 900u, 0u, TASK_CREATE_OPT_NONE);
}

/*
*本文件结束: AppTask.h ===============================================================
*/

