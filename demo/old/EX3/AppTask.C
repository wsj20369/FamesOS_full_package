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

void dpc_for_test(void * d, int nr)
{
    static INT16U i=0;
    INT08S  ts[10];

    prt_string(15, 8, "[", 0);
    prt_string(16, 8, decimal2string(ts, i), 0);
    prt_string(24, 8, "]", 0);
    i+=nr;
}

/*------------------------------------------------------------------------------------
* 函数: TaskMain()
* 说明: 主任务
**----------------------------------------------------------------------------------*/
void far TaskMain(void * data)
{
    INT08S  ts[64], ts2[32];
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
    TimerSet(Timer_for_test, 1L, TIMER_TYPE_AUTO, dpc_for_test, NULL);
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
        prt_string(16,   22, decimal2string(ts, TaskSwitches), 3);
        prt_string(24,   22, "]  Tasks: ", 0);
        prt_string(34,   22, decimal2string3(ts, NumberOfTasks), 0);
        prt_string(44,   22, "CPU: ", 0);
        prt_string(49,   22, decimal2string3(ts, CPU_USED), 0);
        prt_string(52,   22, "%", 0);
        /* 测试INT#toSTR()类函数 */
        prt_string(2,   23, INT32toSTR(ts, TaskSwitches, CHG_OPT_DEC|CHG_OPT_END), 0x1E);
        prt_string(10,  23, INT32toSTR(ts, TaskSwitches, CHG_OPT_END), 0x1E);
        prt_string(20,  23, INT32toSTR(ts, TaskSwitches, CHG_OPT_RAW|CHG_OPT_END), 0x1E);
        prt_string(30,  23, INT32toSTR(ts, TaskSwitches, CHG_OPT_DEC|CHG_OPT_END|CHG_OPT_FRC|0x75), 0x1E);
        prt_string(40,  23, INT32toSTR(ts, TaskSwitches, CHG_OPT_DEC|CHG_OPT_END|CHG_OPT_FIL|5|CHG_OPT_LFT), 0x1E);
        prt_string(50,  23, INT32toSTR(ts, TaskSwitches, CHG_OPT_DEC|CHG_OPT_END|CHG_OPT_FIL|CHG_OPT_ZER|8), 0x1E);
        prt_string(60,  22, INT32toSTR(ts, -TaskSwitches,CHG_OPT_DEC|CHG_OPT_END|CHG_OPT_SIG|CHG_OPT_FRC|0xC6|CHG_OPT_FIL), 0x1A);
        prt_string(60,  23, INT32toSTR(ts, -TaskSwitches,CHG_OPT_DEC|CHG_OPT_END|CHG_OPT_NUL|CHG_OPT_FRC|0xC6|CHG_OPT_FIL), 0x1A);
        /**/
        /* 测试STRtoINT#()类函数
        strcpy(ts2, "     -13256        ");
        prt_string(2,   23, INT32toSTR(ts, (INT32S)STRtoINT32(ts2, CHG_OPT_DEC), CHG_OPT_DEC|CHG_OPT_END|CHG_OPT_SIG), 0x1A);
        */
        /* 测试STRtoSTR()函数
        strcpy(ts2, "123456abcdefgABcDeF000");
        prt_string(2,   23, STRtoSTR(ts2, ts2, CHG_OPT_RVT|CHG_OPT_LOW|CHG_OPT_UPR|10|CHG_OPT_END), 0);
        */

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
    INT08S  ts[16];
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
        prt_string(1,12,"scan start", 3);
        scan_all_nic();
        setup_current_nic();
        prt_string(1,13,"scan end", 4);
    }
    EXIT_CRITICAL();
    
    for(;;){

        prt_string(20, 11, "#NIC#", 0x1E);
        prt_string(20, 13, "VenID" ,0x0);
        prt_string(20, 14, "DevID" ,0x0);
        prt_string(20, 15, "BusNo" ,0x0);
        prt_string(20, 16, "DevFn" ,0x0);
        prt_string(20, 17, "Suppt" ,0x0);
        prt_string(20, 18, "BaseA" ,0x0);
        
        prt_string(30, 11, INT16toSTR(ts, nr_of_nic, CHG_OPT_DEC|CHG_OPT_FIL|4|CHG_OPT_END), 0x1E);
        for(i=0; i<nr_of_nic; i++) {
            prt_string(30+10*i,13,INT16toSTR(ts,(INT16S)nic_in_system[i].VendorID, CHG_OPT_END) ,0);
            prt_string(30+10*i,14,INT16toSTR(ts,(INT16S)nic_in_system[i].DeviceID, CHG_OPT_END) ,0);
            prt_string(30+10*i,15,INT16toSTR(ts,(INT16S)nic_in_system[i].BusNo, CHG_OPT_END) ,0x0);
            prt_string(30+10*i,16,INT16toSTR(ts,(INT16S)nic_in_system[i].DeviceFuncNo, CHG_OPT_END) ,0x0);
            prt_string(30+10*i,17,INT16toSTR(ts,(INT16S)nic_in_system[i].Supported, CHG_OPT_END) ,0x0);
            prt_string(30+10*i,18,INT16toSTR(ts,(INT16S)pci_get_base_addr_io(nic_in_system[i].BusNo, nic_in_system[i].DeviceFuncNo), CHG_OPT_END) ,0x0);
        }

        prt_string(2, 24, "Demonstration of Task-Dispatches & TaskList-Movements --- Jun(FamesOS-", 0);
        prt_string(72,24, FamesOS_VersionString")", 0);
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

