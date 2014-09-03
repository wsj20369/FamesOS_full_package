/*************************************************************************************
** 文件: AppTask.C
** 说明: 用户任务定义
** 作者: Jun
** 时间: 2010-6-26
*************************************************************************************/
#define  FAMES_AppTask_C
#include <famesos.h>
#include "app.h"
#include "appver.h"

/*lint -e830 -e768 -e755 -e757 -e756 -e750 -e714 -e526 -e677 -w3 -wlib(0)*/

    static INT16S x[24]={0,};
    static INT16S m[16]={0,};
    static INT16S y[16]={0,};
    static INT16S r4192=0;
    static INT16S r2000=0;
    static INT16S y5;
    
    static PLC_ITEM item_x = define_plc_item(FATEK_PLC_READ_M, "X0000", x, 24, 0,   NULL);
    static PLC_ITEM item_m = define_plc_item(FATEK_PLC_READ_M, "M0000", m, 16, 10,   &item_x);
    static PLC_ITEM item_y = define_plc_item(FATEK_PLC_READ_M, "Y0000", y, 16, 0, &item_m);
    static PLC_ITEM item_y5 = define_plc_item(FATEK_PLC_WRITE_M, "Y0005", &y5, 1, 0, &item_y);
    static PLC_ITEM item_r4192 = define_plc_item(FATEK_PLC_READ_R, "R04192", &r4192, 1, 0, &item_y5);
    static PLC_ITEM item_r2000 = define_plc_item(FATEK_PLC_READ_R, "R02000", &r2000, 1, 0,  &item_r4192);



dumpstr(char * s, int len)
{
    int i;
    DispatchLock();
    printf("\nlen=%d\n", len);
    for(i=0; i<len; i++)printf(" %02X ", 0xff&s[i]);
    DispatchUnlock();
}


MutexCB  mutex_testkey;

INT16U testkey(void)
{
    return (INT16U)GetKey();
}

void prt_string(int x, int y, char * s, char color)
{
    textprintstr(x, y, s, color);
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

    clrscr();
    textprintdec32(57, 16, SecondsFromStart, 0x4e, CHG_OPT_FIL|13|CHG_OPT_LFT);

    y5 = !y5;

    i+=nr;
}

void far TaskDumpArp(void * data);

/*------------------------------------------------------------------------------------
* 函数: TaskMain()
* 说明: 主任务
**----------------------------------------------------------------------------------*/
void far TaskMain(void * data)
{
    INT08S  ts[64], ts2[32];
    INT16S  chg_opt=0x8E10;
    INT16U key;
    static INT16S yyy=1, tx_packets=0;
    static char tx_data[]="\xFF\xFF\xFF\xFF\xFF\xFF\x11\x22\x33\x44\x55\x66\x77\x88\x01\x00";

    InitStat();
    TimerInit();
    DispatchLock();
    TaskCreate(TaskTest, (void*)12,  "Task4", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)12,  "Task5", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)11,  "Task6", 512u, 9u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)15,  "Task7", 512u, 0u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)13,  "Task8", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskDumpArp, (void*)3,"TaskDumpArp", 512u, 4u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTestPLC, NULL, "TestPLC", 512, 5, TASK_CREATE_OPT_NONE);
    DispatchUnlock();
     
    TimerSet(Timer_for_test, 500L, TIMER_TYPE_AUTO, dpc_for_test, NULL);
    
    while(1){
        switch(key=testkey()){
            case 0x1b:
                nic_stop();
                ExitApplication();
            case 0x4: /*Ctrl-D*/
                break;
                TaskDelete(CurrentTask);
                break;
            case 0x13:
                break;
                if(!TaskDelete(TaskStatHandle)){
                }
                break;
            case 0x3:
                break;
                TaskCreate(TaskStat, NULL, "#STAT", 1024, TaskStatPrio, TASK_CREATE_OPT_NONE);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':        
            case '6':
            case '7':
            case '8':
            case '9':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                key=CHARtoHEX(key);
                if(key==0)key=16;
                chg_opt&=0xff00;
                chg_opt|=key;
                break;
            case 0x3b00:
            case 0x3c00:
            case 0x3d00:
            case 0x3e00:
            case 0x3f00:
            case 0x4000:
            case 0x4100:
            case 0x4200:
                key>>=8;
                key-=0x3b;
                key+=8;
                key=(0x1<<key);
                chg_opt ^= key;
                break;
            case BACKSPACE:
                PutKey(0x31);
                PutKey(0x32);
                PutKey(0x33);
                PutKey(0x34);
                PutKey(0x35);
                PutKey(0x36);
                PutKey(0x37);
                PutKey(0x38);
                PutKey(0x39);
                PutKey(0x41);
                PutKey(0x42);
                PutKey(0x43);
                PutKey(0x44);
                PutKey(0x45);
                PutKey(0x30);
                PutKey(0x8); /*
                get_mac(0x1600a8c0);*/
                break;
            case ENTER:
                ClrKey();
                break;
            case TAB:
                clrscr();
                break;
            default:
                break;
        }
        #if 1
        if(key){
            yyy = 24;
            prt_string(45, yyy, "[", 0);
            prt_string(46, yyy, uint2string(ts,key), 0);
            prt_string(50, yyy, ", ", 0);
            prt_string(52, yyy, ((key&0xff)?char2str(ts, key):" "), 0);
            prt_string(54, yyy, "]", 0);
        }
        #endif
        #if 1
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

        prt_string(2,   15, INT16toSTR(ts, chg_opt, CHG_OPT_END),  0x1e);
        prt_string(2,   16, INT32toSTR(ts, TaskSwitches, chg_opt), 0x1e);
        prt_string(2,   17, INT32toSTR(ts, -TaskSwitches,chg_opt), 0x1e);
        /**/
        /* 测试STRtoINT#()类函数
        */
        strcpy(ts2, "   -313256        ");
        prt_string(2,   21, INT32toSTR(ts, (INT32S)STRtoINT32(ts2, CHG_OPT_DEC), CHG_OPT_DEC|CHG_OPT_END|CHG_OPT_SIG), 0x1A);
        
        /* 测试STRtoSTR()函数
        strcpy(ts2, "123456abcdefgABcDeF000");
        prt_string(2,   23, STRtoSTR(ts2, ts2, CHG_OPT_RVT|CHG_OPT_LOW|CHG_OPT_UPR|10|CHG_OPT_END), 0);
        */
        prt_string(60,  21, INT32toSTR(ts, INT16XCHG(0x1234),CHG_OPT_END), 0);

        prt_string(40, 16, "Running: ", 0x1A);
        prt_string(50, 16, INT32toSTR(ts, SecondsFromStart,CHG_OPT_END|CHG_OPT_DEC), 0x1E);

        prt_string(57, 14, "Link: ", 0);
        prt_string(63, 14, nic_islink()?"OK":"NO", 0);
        textprintdec32(69, 14, eth_stat.rx_packets, 0, 0);
        textprintdec32(74, 14, eth_stat.tx_packets, 0, 0);

        #endif

        TaskSleep(10L);
    }
}

/*------------------------------------------------------------------------------------
* 函数: TaskTest()
* 说明: PLC测试任务
**----------------------------------------------------------------------------------*/
long PLC_COM_BR=38400L;

void far TaskTestPLC(void * data)
{
    INT16S i,row;
    static INT16S r2000;
    static PLC_ITEM reset_r2000 = define_plc_item(FATEK_PLC_WRITE_R, "R02000", &r2000, 1, 0, NULL);

    init_plc_item_list(&item_r2000, &item_x);

    open_plc();

    r2000 = 0;

    plc_action(&reset_r2000);

    row=10;
    while(1){
        textprintstr(1, row,   "X:", 13);
        textprintstr(1, row+1, "Y:", 13);
        textprintstr(1, row+2, "M:", 13);
        for(i=0; i<24; i++)
            textprintdec16(4+i, row,   x[i], x[i]?11:8, CHG_OPT_NUL);
        for(i=0; i<16; i++)
            textprintdec16(4+i, row+1, y[i], y[i]?13:8, CHG_OPT_NUL);
        for(i=0; i<16; i++)
            textprintdec16(4+i, row+2, m[15-i], m[15-i]?13:8, CHG_OPT_NUL);
        
        textprintdec32(40, row,   item_x.count, 11, CHG_OPT_NUL);
        textprintdec32(40, row+1, item_y.count, 13, CHG_OPT_NUL);
        textprintdec32(40, row+2, item_m.count, 13, CHG_OPT_NUL);
        TaskSleep(10L);
        
    }
}

/*------------------------------------------------------------------------------------
* 函数: TaskTest()
* 说明: 测试任务
**----------------------------------------------------------------------------------*/
void far TaskTest(void * data)
{
    static INT16U flag=0;
    INT16U xmshandles = 0;

    if(flag)while(1){
        TaskSleep(CurrentTask *20L);
        DispatchLock();
        printf("I\'m task: %s\n", CurrentTCB->TaskName);
        DispatchUnlock();
        TaskCreate(TaskTest, (void*)12,  "test created by test", 512u, 3u, TASK_CREATE_OPT_NONE);
        TaskSleep(CurrentTask * 500L);
        return;
    }

    flag = 1;

    if(!XMSinit()){
        DispatchLock();
        printf("xms initialize fail!\n");
        getch();
        DispatchUnlock();
        return;
    }
        while(XMSalloc(320))xmshandles++;
        DispatchLock();
        printf("xms allocated %d\n", xmshandles);
        DispatchUnlock();  

}

/*------------------------------------------------------------------------------------
* 函数: TaskTest()
* 说明: 测试任务
**----------------------------------------------------------------------------------*/
void far TaskTestNET(void * data)
{
    INT16S tdata;
    INT32U runs=0;
    BOOL   ddddd=NO;
    static INT16S rx_packets=0, tx_packets=0;
    INT08S ts[16];
    static INT08S rx_buf[2048], icmp_message[512];
    INT16S rx_len;
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
        DispatchLock();
        #if 1
        prt_string(57, 14, "Link: ", 0);
        prt_string(63, 14, nic_islink()?"OK":"NO", 0);
        textprintdec32(69, 14, eth_stat.rx_packets, 0, 0);
        textprintdec32(74, 14, eth_stat.tx_packets, 0, 0);
        #endif
        #if 1
        if(get_icmp_message(icmp_message)){
            printf("%s\n", icmp_message);
        }
        if(get_tftpd_message(icmp_message)){
            printf("%s\n", icmp_message);
        }
        #endif
        DispatchUnlock();
        TaskSleep(10L);
    }
}

void far TaskDumpArp(void * data)
{
    INT16S  i;
    char buf[64];
    char *icmp_data="jun send this icmp echo request packet to 192.168.0.22!!!";

    arp_initialize(); 
    if(TaskCreate(TaskNIC, NULL, "TaskNIC", 1024, PRIO_NET, TASK_CREATE_OPT_NONE)){
    } else {
        prt_string(1,1, "TaskDumpArp Create failure!", 0);
        TaskSuspend(CurrentTask);
    } 

    return;
    
    for(;;){
        DispatchLock();
        prt_string(32, 2, "Arp Table: ------------------------------", 0);
        for(i=0; i<6; i++){
            memset(buf, ' ', 45);buf[45]=0;
            if(arp_table[i].timeout == 0){
                prt_string(32, 3+i, buf, 0);
                continue;
            }
            sprintf(buf, "%d.%d.%d.%d", (int)(arp_table[i].ip &0xff),
                         (int)((arp_table[i].ip>>8) &0xff),
                         (int)((arp_table[i].ip>>16) &0xff),
                         (int)((arp_table[i].ip>>24) &0xff));
            buf[strlen(buf)]=' ';
            sprintf(&buf[18], "%02X:%02X:%02X:%02X:%02X:%02X   %-4d",
                         (int)(arp_table[i].ha[0]),
                         (int)(arp_table[i].ha[1]),
                         (int)(arp_table[i].ha[2]),
                         (int)(arp_table[i].ha[3]),
                         (int)(arp_table[i].ha[4]),
                         (int)(arp_table[i].ha[5]), arp_table[i].timeout);
            prt_string(32, 3+i, buf, 0); 
        }
        prt_string(32, 3+i, "-----------------------------------------", 0);
        DispatchUnlock();
        TaskSleep(50);
        /*
        send_echo(ICMP_ECHO, 0, 0, 0, (192L+ (168L<<8) + (0L<<16) + (22L<<24)), icmp_data, strlen(icmp_data));
        */
    }
}


/*------------------------------------------------------------------------------------
* 函数: TaskTest()
* 说明: 测试任务
**----------------------------------------------------------------------------------*/
void far TaskTest2(void * data)
{
    INT16S tdata;
    INT32U runs=0;
    BOOL   ddddd=NO;
    static INT16S rx_packets=0, tx_packets=0;
    INT08S ts[16];
    INT08S rx_buf[2048];
    INT16S rx_len;
    INT16S namey=2, statey=12;
    INT16S readyy=40, sleepy=60;
    PRIOMAP_TYPE tpt;
    TCB * ptcb;
    INT16S i,j,k;
    static INT16S clrscr_flag=1;
    static char tx_data[]="\xFF\xFF\xFF\xFF\xFF\xFF\x00\x11\x22\x33\x44\x55\x66\xAA\x55\x00\x00";

    tdata=(INT16S)data;
    tdata+=1;

    ENTER_CRITICAL();
    if(clrscr_flag){
        clrscr();
        clrscr_flag=0;
        prt_string(1,12,"scan start", 3);
        scan_all_nic();
        setup_current_nic();
        nic_open();
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
        prt_string(20, 19, "Init:" ,0x0);
        
        prt_string(30, 11, INT16toSTR(ts, nr_of_nic, CHG_OPT_DEC|CHG_OPT_FIL|4|CHG_OPT_END), 0x1E);
        for(i=0; i<nr_of_nic; i++) {
            prt_string(30+10*i,13,INT16toSTR(ts,(INT16S)nic_in_system[i].VendorID, CHG_OPT_END) ,0);
            prt_string(30+10*i,14,INT16toSTR(ts,(INT16S)nic_in_system[i].DeviceID, CHG_OPT_END) ,0);
            prt_string(30+10*i,15,INT16toSTR(ts,(INT16S)nic_in_system[i].BusNo, CHG_OPT_END) ,0x0);
            prt_string(30+10*i,16,INT16toSTR(ts,(INT16S)nic_in_system[i].DeviceFuncNo, CHG_OPT_END) ,0x0);
            prt_string(30+10*i,17,INT16toSTR(ts,(INT16S)nic_in_system[i].Supported, CHG_OPT_END) ,0x0);
            prt_string(30+10*i,18,INT16toSTR(ts,(INT16S)pci_get_base_addr_io(nic_in_system[i].BusNo, nic_in_system[i].DeviceFuncNo), CHG_OPT_END) ,0x0);
        }

        prt_string(40, 17, "Link: ", 0);
        prt_string(46, 17, nic_islink()?"OK":"NO", 0);
        if(nic_poll(rx_buf, &rx_len))rx_packets++;
        if(nic_xmit(tx_data, 18))tx_packets++;
        tx_data[14]++;
        textprintdec16(50, 17, rx_packets, 0, 0);
        textprintdec16(60, 17, tx_packets, 0, 0);

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
void apical TaskSwitchHook(void)
{
}

/*------------------------------------------------------------------------------------
* 函数: InitApplication()
* 说明: 初始化应用程序, 在InitFamesOS()中调用
**----------------------------------------------------------------------------------*/
void apical InitApplication(void)
{
    INT32U LocalIP = 192L+ (168L<<8) + (0L<<16) + (68L<<24);
    CALLED_ONLY_ONCE();
    /*LocalIP = 0x64L + (0xc0L<<24) + (0xa8L<<16);*/
    MutexInit(&mutex_testkey);
    set_local_ip(LocalIP);
    clrscr();
    TaskCreate(TaskMain, (void*)0, "main", 900u, PRIO_STARTUP, TASK_CREATE_OPT_NONE);
}

/*
*本文件结束: AppTask.h ===============================================================
*/

