/*************************************************************************************
** 文件: AppTask.C
** 说明: 用户任务定义
** 作者: Jun
** 时间: 2010-6-26
*************************************************************************************/
#define  FAMES_AppTask_C
#include <includes.h>
#include "app.h"
#include "appver.h"

/*lint -e830 -e768 -e755 -e757 -e756 -e750 -e714 -e526 -e677 -w3 -wlib(0)*/

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

    #if 1
    prt_string(55, 9, "                     ", 0);
    prt_string(55, 10, "Second:   ", 0);
    textprintdec32(63, 10, SecondsFromStart, 0x4e, CHG_OPT_FIL|0xC3|CHG_OPT_FRC|CHG_OPT_LFT);
    #else
    gotoxy(55, 10);
    printf("Second:   %ld", SecondsFromStart);
    #endif
    
    i+=nr;
}

HANDLE maintask=InvalidHandle;

GUI_FORM  form_a, form_b, form_c;

BOOL callback window_0_proc(WINDOW * window, MSGCB * win_msg)
{
    KEYCODE key;
    MSGCB   msg;

    key = NONEKEY;

    FamesAssert(win_msg);
    FamesAssert(window);

    switch(win_msg->msg){
        case GUI_MSG_KEYSTROKE:
            key = (KEYCODE)win_msg->wParam;
            break;
        default:
            break;
    }
    if(key){
        printf("keypressed %04X in window %d\n", key, window - window_0);

        msg.msg=GUI_MSG_KEYSTROKE;
        msg.wParam = (WPARAM)key;

        SendMessage(maintask, &msg);

        if(key == '1'){
            msg.msg=GUI_MSG_SWITCH_WINDOW;
            if(current_window == window_0)
                msg.wParam=(WPARAM)window_1;
            else 
                msg.wParam=(WPARAM)window_0;
            SendMessage(gui_service_get_handle(), &msg);
        }
    }
        
    return ok;
}


void prepare_windows()
{
    gui_init_form(&form_a);
    gui_init_form(&form_b);
    gui_init_form(&form_c);

    form_a.backcolor = 32;
    form_a.rect.x = 200;
    form_a.rect.y = 200;
    form_b.backcolor = 72;
    form_b.rect.x = 100;
    form_b.rect.y = 100;
    form_c.backcolor = 123;
    form_c.rect.x = 300;
    form_c.rect.y = 300;

    gui_window_connect(window_0, &form_a);
    gui_window_connect(window_1, &form_b);
    gui_window_connect(window_1, &form_c);
    gui_window_connect(window_0, &form_c);

    gui_window[0].window_proc = window_0_proc;
    gui_window[1].window_proc = window_0_proc;

    gui_create_window(window_0, 0);
    gui_create_window(window_1, 0);
}








void far TaskDumpArp(void * data);

HANDLE rcv_msg_handle=InvalidHandle;
HANDLE snd_msg_handle=InvalidHandle;

/*------------------------------------------------------------------------------------
* 函数: TaskMain()
* 说明: 主任务
**----------------------------------------------------------------------------------*/
void far TaskMain(void * data)
{
    INT08S  ts[64], ts2[32];
    INT16S  chg_opt=0x8E10;
    MSGCB   MSG;
    INT16U key;
    INT08U red=0, green=0, blue=0;
    static INT16S yyy=1, tx_packets=0;
    static char tx_data[]="\xFF\xFF\xFF\xFF\xFF\xFF\x11\x22\x33\x44\x55\x66\x77\x88\x01\x00";
    BOOL   fff=0;

    InitStat();
    TimerInit();
    (void)InitGUI();
    DispatchLock();
    TaskCreate(TaskTest, (void*)12,  "Task4", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)12,  "Task5", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)11,  "Task6", 512u, 9u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)15,  "Task7", 512u, 0u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void*)13,  "Task8", 512u, 3u, TASK_CREATE_OPT_NONE);
    rcv_msg_handle=TaskCreate(rcv_msg, (void*)13,  "TaskRcv", 512u, 6u, TASK_CREATE_OPT_NONE);
    snd_msg_handle=TaskCreate(TaskSendMsg, (void*)13,  "TaskSendMsg", 512u, 7u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskDumpArp, (void*)3,"TaskDumpArp", 512u, 4u, TASK_CREATE_OPT_NONE);
    DispatchUnlock();
    
    TimerSet(Timer_for_test, 10L, TIMER_TYPE_AUTO, dpc_for_test, NULL);

    SetKeyBufTask(CurrentTask);
    /*
    prepare_windows();
    */
    while(1){        
        key = testkey();
        if(key == 0){
            GetMessage(&MSG);
            if(MSG.msg == GUI_MSG_KEYSTROKE)
                key = (KEYCODE)MSG.wParam;
        }
        switch(key){
            case 'x': case 'X':
                break;
                MSG.msg=GUI_MSG_OPEN_X;
                SendMessage(gui_service_get_handle(), &MSG);
                break;
            case 'z': case 'Z':
                break;
                MSG.msg=GUI_MSG_STOP_X;
                SendMessage(gui_service_get_handle(), &MSG);
                break;
            case 0x1b:
                nic_stop();
                ExitApplication();
            case 0x4: /*Ctrl-D*/
                TaskDelete(CurrentTask);
                break;
            case 0x13:
                if(!TaskDelete(TaskStatHandle)){
                }
                break;
            case 0x3: /*Ctrl-C*/
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
                PutKey(0x8);
                get_mac(0x6400a8c0);
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
            yyy = 12;
            prt_string(55, yyy-1, "                      ", 7);
            prt_string(55, yyy, "Key:   ", 7);
            prt_string(63, yyy, "[", 7);
            prt_string(64, yyy, uint2string(ts,key), 7);
            prt_string(68, yyy, ", ", 7);
            prt_string(70, yyy, ((key&0xff)?char2str(ts, key):" "), 7);
            prt_string(72, yyy, "]", 7);
            MSG.msg=key;
            SendMessage(snd_msg_handle, &MSG);
        }
        #endif
        #if 0
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

        prt_string(2,   15, INT16toSTR(ts, chg_opt, CHG_OPT_END),  0x10);
        prt_string(2,   16, INT32toSTR(ts, TaskSwitches, chg_opt), 0x10);
        prt_string(2,   17, INT32toSTR(ts, -TaskSwitches,chg_opt), 0x10);
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

        #endif

        TaskSleep(50L);
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
    static INT08S old_tftp_msg[22]={'x', };
    static char nic_name[16];

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
        prt_string(55, 3, "                     ", 0);
        prt_string(55, 4, "Name:     ", 0);
        MEMCPY(nic_name, CurrentNIC==NULL?"#NONE#      ":CurrentNIC->NicDriver->NicName, 10);
        nic_name[10]='\0';
        prt_string(65, 4, nic_name, 0);
        prt_string(55, 5, "Link:     ", 0);
        prt_string(65, 5, nic_islink()?"OK          ":"NO          ", 0);
        prt_string(55, 6, "RX:       ", 0);
        textprintdec32(65, 6, eth_stat.rx_packets, 0, 0);
        prt_string(55, 7, "TX:       ", 0);
        textprintdec32(65, 7, eth_stat.tx_packets, 0, 0);
        prt_string(55, 8, "CPU:      ", 0);
        textprintdec16(64, 8, CPU_USED, 0, CHG_OPT_FIL|3);
        prt_string(67, 8, "%         ", 0);
        prt_string(55, 14, "OS-VER:   "FamesOS_VersionString, 0);
        #endif
        #if 1
        if(get_icmp_message(icmp_message)){
            old_tftp_msg[0]='x';
            if(MEMCMP(icmp_message, old_tftp_msg, 18))printf("\n");
            else printf("\r");
            printf("%s", icmp_message);
            MEMCPY(old_tftp_msg, icmp_message, 20);
        }
        if(get_tftpd_message(icmp_message)){            
            if(MEMCMP(icmp_message, old_tftp_msg, 18))printf("\n");
            else printf("\r");
            printf("%s", icmp_message);
            MEMCPY(old_tftp_msg, icmp_message, 20);
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
    for(;;){
        
        return;
        
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
        #if 0
        setup_current_nic();
        #endif
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
void APICAL TaskSwitchHook(void)
{
}


INT16S send_msg=0;

BOOL msghdlr(HANDLE task, MSGCB * m)
{
    textprintstr(55, 21, "Message:", 0);
    textprintchar(64, 21, (INT08S)m->msg, 0);
    textprintdec32(73, 21, SecondsFromStart, 0, 0);
    send_msg=1;
}

void far TaskSendMsg(void * data)
{
    MSGCB msg, rx_msg;

    InitMessage(&msg);

    lock_kernel();
    CurrentTCB->msg_handler = msghdlr;
    unlock_kernel();
    
    while(1){
        if(send_msg){
            SendMessage(rcv_msg_handle, &msg);
            msg.msg++;
            send_msg=0;
        } else {
            TaskSleep(10L);
        }
    }
}

BOOL rx_msghdlr(HANDLE task, MSGCB * m)
{
    textprintstr(70, 23, "RX:", 0);
    textprintdec16(73, 23, m->msg, 0, 0);
    textprintdec32(73, 24, SecondsFromStart, 0, 0);
}


void far rcv_msg(void * data)
{
    MSGCB msg;
    INT08U red=0, green=0, blue=0;
    textprintstr(55, 22, "rcv_msg start", 0);
    lock_kernel();
    CurrentTCB->msg_handler = rx_msghdlr;
    unlock_kernel();
    while(1){
        if(WaitMessage(&msg, 5000L)){
            textprintdec16(55, 23, msg.msg, 0, 0);
            blue++;
            if(blue==64){
                green++;
                blue=0;
            }
            if(green==64){
                red++;
                green=0;
            }
            if(red==64)red=0;
            gdi_set_palette(100, red, green, blue);
        } else {
            textprintstr(55, 23, "TM", 4);
        }
    }
}

/*------------------------------------------------------------------------------------
* 函数: InitApplication()
* 说明: 初始化应用程序, 在InitFamesOS()中调用
**----------------------------------------------------------------------------------*/
INT16S irq7(void)
{
    static int i=0;
    textprintstr(55, 16, "Irq7 occured:", 0);
    textprintdec16(70, 16, ++i, 0, CHG_OPT_FIL|8|CHG_OPT_LFT);
    return fail;
}

void APICAL InitApplication(void)
{
    INT32U LocalIP = 192L+ (168L<<8) + (0L<<16) + (68L<<24);
    CALLED_ONLY_ONCE();
    /*LocalIP = 0x64L + (0xc0L<<24) + (0xa8L<<16);*/
    MutexInit(&mutex_testkey);
    set_local_ip(LocalIP);
    IrqConnect(7, irq7);
    maintask=TaskCreate(TaskMain, (void*)0, "Task2", 900u, 0u, TASK_CREATE_OPT_NONE);
}

void APICAL InitApplication2(void)
{
    long i;

    while(1)
    for(i=0; i<0x7FFFFFFFL; i++)
        textprinthex32(5, 12, i, 0);
}


/*
*本文件结束: AppTask.h ===============================================================
*/

