/*************************************************************************************
 * 文件: start.c
 *
 * 说明: 演示
 *
 * 作者: Jun
 *
 * 时间: 2010-12-17
*************************************************************************************/
#define  FAMES_DEMO_START_C
#include <includes.h>
#include "common.h"


/*lint -esym(534, fprintf, fclose)*/
/*lint -esym(534, gui_create_window, gui_window_connect)*/
/*lint -e534, 干脆全禁了它:)*/

void dumpstr(INT08S * s, __int len)
{
    __int i;
    DispatchLock();
    printf("\nlen=%d\n", len);
    for(i=0; i<len; i++)printf(" %02X ", 0xff&s[i]);
    DispatchUnlock();
}

INT16U testkey(void)
{
    return getkey();
}

void prt_string(__int x, __int y, INT08S __far * s, INT08U color)
{
    textprintstr(x, y, s, color);
}


INT08S * uint2string(INT08S * dst, INT16U data)
{
    __int  i;

    for(i=3; i>=0; i--){
        dst[i]=HEXCHAR[(data)&0xf];
        data>>=4;
    }
    dst[4]=0;
    return dst;
}

INT08S * ulong2string(INT08S * dst, INT32U data)
{
    __int  i;

    for(i=7; i>=0; i--){
        dst[i]=HEXCHAR[(data)&0xfL];
        data>>=4L;
    }
    dst[8]=0;
    return dst;
}

INT08S * decimal2string(INT08S * dst, INT16U data)
{
    __int  i;

    for(i=5; i>=0; i--){
        dst[i]=HEXCHAR[(data)%10];
        data/=10;
    }
    dst[6]=0;
    return dst;
}

INT08S * decimal2string3(INT08S * dst, INT16U data)
{
    __int  i;

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


INT08S * uint2char(INT08S * dst, INT16U data)
{
    dst[0]=HEXCHAR[data&0xf];
    dst[1]=0;
    return dst;
}

INT08S * char2str(INT08S * dst, __char c)
{
    dst[0]=c;
    dst[1]=0;
    return dst;
}


/*------------------------------------------------------------------------------------
 *  取系统的时间日期
**----------------------------------------------------------------------------------*/
void GetDateTime (INT08S *s)
{
    struct time now;
    struct date today;

    gettime(&now);
    getdate(&today);
    (void)sprintf(s, "%02d-%02d-%02d  %02d:%02d:%02d",
               today.da_mon,
               today.da_day,
               today.da_year,
               now.ti_hour,
               now.ti_min,
               now.ti_sec);
}

long dpc_for_test_speed = 500L;

extern BMPINFO info[];
extern gui_control __far * pic1;
__int xxx=0;

void dpc_for_test(void __far * d, __int nr)
{
    extern gui_control __far * sys_monitor;
    #if 1
    prt_string(55, 9, "                     ", 0);
    prt_string(55, 10, "Second:   ", 0);
    textprintdec32(63, 10, (INT32S)SecondsFromStart, 0x4e, CHG_OPT_FIL|0xC3|CHG_OPT_FRC|CHG_OPT_LFT);
    d  = d;
    nr = nr;
    #else
    static __int i=0;
    gotoxy(55, 10);
    printf("Second:   %ld", SecondsFromStart);
    i+=nr;
    #endif
    plc_scan_y[0]++;
    xxx++;
    xxx%=6;
    gui_picture_set_picture(pic1, &info[xxx]);
    gui_refresh_control(sys_monitor);
}

HANDLE maintask=InvalidHandle;


void __far TaskDumpArp(void __far * data);

HANDLE rcv_msg_handle=InvalidHandle;
HANDLE snd_msg_handle=InvalidHandle;

/*------------------------------------------------------------------------------------
* 函数: TaskMain()
* 说明: 主任务
**----------------------------------------------------------------------------------*/
void clr(void)
{
    clrscr();
    printf("screen cleared\n");
}

MSGCB abc;

void hook1(KEYCODE key)
{
    abc.lock = NO;
    abc.msg  = SYS_MSG_KEY;
    abc.wParam = (WPARAM)key;
    /*
    PostMessage(maintask, &abc);
    */
    printf("hook1: %04X\n", key);
    if(key == F1)DeregisterSpecialKey('S');
}

void sk_s1(void)
{printf("special key S1\n");
}
void sk_s2(void)
{printf("special key S2, free-memory = %ld\n", get_free_mem());
}

void __far stack_monitor(void __far *d)
{
    FILE * fp;
    INT32S s[12];
    int i;
    
    for(;;){
        fp = fopen("stack.txt", "a+t");
        if(fp){
            fprintf(fp, "handle  buf        btm        ptr          total    used     remain   state   prio   name \n");
            for(i=0; i<MAX_TASKS; i++){
                if(TCBS[i].TcbUsed != TCB_USED_YES)continue;
                s[0] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_GET_BUF);
                s[1] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_GET_BTM);
                s[2] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_GET_PTR);
                s[3] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_TOTAL);
                s[4] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_USED);
                s[5] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_REMAIN);
                fprintf(fp, "  %2d    %p  %p  %p    %-6ld   %-6ld %c %-6ld   %s   %-6d %s\n", 
                             i, s[0], s[1], s[2], s[3], s[4], ((s[5]<32L)?'*':' '), s[5], 
                             ((TCBS[i].TaskState==0)?"     ":"SLEEP"),
                             TCBS[i].Priority, TCBS[i].TaskName);/*lint !e559 !e622*/
            }
            fprintf(fp, "\ntasks: %-4d free-memory: %-8ld  switches: %-8ld  seconds-from-start: %ld\n",
                         NumberOfTasks, get_free_mem(), TaskSwitches, SecondsFromStart);
            fprintf(fp, "--------------------------------------------------------------------------------------\n");
            fclose(fp); 
        } else {
            printf("!!! stack_monitor: file open error! !!!\n");
        }
        TaskSleep(10L);
    }
}

INT16S irq7(void)
{
    static int i=0;
    textprintstr(55, 16, "Irq7 occured:", 0);
    textprintdec16(70, 16, ++i, 0, CHG_OPT_FIL|8|CHG_OPT_LFT);
    return fail;
}

void __far __task start(void __far * data)
{
/*lint --e{529}*/
    INT08S  ts[64], ts2[32];
    INT16U  chg_opt=0x8E10;
    MSGCB   MSG;
    INT16U key;
    INT08U red=0, green=0, blue=0;
    static INT16S yyy=1, tx_packets=0;
    static char tx_data[]="\xFF\xFF\xFF\xFF\xFF\xFF\x11\x22\x33\x44\x55\x66\x77\x88\x01\x00";
    BOOL   fff=0;
    void __far * fpp;

    chg_opt = chg_opt;
    LOG_INIT();
    fpp=mem_alloc(5000uL);
    printf("fpp=%p, free-mem=%ld\n", fpp, get_free_mem());/*lint !e559*/
    maintask = CurrentTask;
    DispatchLock();
    TaskCreate(TaskTest, (void __far *)12,  "Task4", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void __far *)12,  "Task5", 512u, 3u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void __far *)11,  "Task6", 512u, 9u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void __far *)15,  "Task7", 512u, 2u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskTest, (void __far *)13,  "Task8", 512u, 3u, TASK_CREATE_OPT_NONE);
    rcv_msg_handle=TaskCreate(rcv_msg, (void __far *)13,  "TaskRcv", 512u, 6u, TASK_CREATE_OPT_NONE);
    snd_msg_handle=TaskCreate(TaskSendMsg, (void __far *)13,  "TaskSendMsg", 512u, 7u, TASK_CREATE_OPT_NONE);
    TaskCreate(TaskDumpArp, (void __far *)3,"TaskDumpArp", 512u, 4u, TASK_CREATE_OPT_NONE);
    #if 0
    TaskCreate(stack_monitor, NULL, "stk-monitor", 1024, 1, TASK_CREATE_OPT_NONE);
    #endif
    DispatchUnlock();
    
    TimerSet(Timer_for_test, dpc_for_test_speed, TIMER_TYPE_AUTO, dpc_for_test, NULL);

    set_local_ip(0x4400A8C0uL); /* 192.168.0.68 */

    example_init_xms();

    InitPLCService();
    #if 1
    demo_init_plc();
    #endif

    #if 1
    demo_init_gui();
    #endif

    example_init_udp_port();
    
    IrqConnect(7, irq7);

    RegisterSpecialKey(TAB, clr);
    #if 0
    RegisterKeyHook(hook1);
    #endif
    RegisterSpecialKey('S', sk_s1);
    RegisterSpecialKey('S', sk_s2);

    OpenConsole();
   
    /*
    prepare_windows();
    */
    for(;;){        
        key = testkey();
        if(key == 0 && GetMessage(&MSG)){
            if(MSG.msg == SYS_MSG_KEY)
                key = (KEYCODE)MSG.wParam;
        }
        switch(key){/*lint --e{527}*/
            case 'x': case 'X':
                break;
            case 'z': case 'Z':
                break;
            case 0x1b:
                nic_stop();
                ExitApplication();
                break;
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
                key=(INT16U)CHARtoHEX((INT08S)key);
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
                break;
                get_mac(0x6400a8c0);
                break;
            case ENTER:
                break;
            case 't': case 'T':
                if(1){
                    DrawFont(100, 100, "我是中国人, I am Jun!"
                        , 0, 0, 0);
                }
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
            prt_string(70, yyy, ((key&0xff)?char2str(ts, (__char)key):" "), 7);
            prt_string(72, yyy, "]", 7);
            MSG.msg=(INT16S)key;
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
void __far TaskTest(void __far * data)
{
/*lint --e{529}*/
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
    static INT08S old_tftp_msg[22]="X";
    static char nic_name[16];

    data = data; /*lint !e507*/

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
        textprintdec16(64, 8, (INT16S)CPU_USED, 0, CHG_OPT_FIL|3);
        prt_string(67, 8, "%         ", 0);
        prt_string(55, 14, "OS-VER:   "FamesOS_VersionString, 0);
        prt_string(1, 12, "PLC-R4151: ", 0);
        textprintdec16(12, 12, r4151, 0, CHG_OPT_FRC|0x53|CHG_OPT_FIL);
        prt_string(1, 14, "PLC-X: ", 0);
        prt_string(1, 16, "PLC-Y: ", 0);
        if("dump x & y"){
            __char _s[20];
            static __int x7_up=0, x9_up=0, x11_up=0, x18_up=0, x20_up=0;
            INT16toBINSTR(_s, plc_x[0], CHG_OPT_END);
            STRtoSTR(_s, _s, CHG_OPT_RVT);
            textprintstr(8,  14, _s, 0);
            INT16toBINSTR(_s, plc_x[1], CHG_OPT_END);
            STRtoSTR(_s, _s, CHG_OPT_RVT);
            textprintstr(24, 14, _s, 0);
            
            INT16toBINSTR(_s, plc_y[0], CHG_OPT_END);
            STRtoSTR(_s, _s, CHG_OPT_RVT);
            textprintstr(8,  16, _s, 0);
            INT16toBINSTR(_s, plc_y[1], CHG_OPT_END);
            STRtoSTR(_s, _s, CHG_OPT_RVT);
            textprintstr(24, 16, _s, 0);

            #if 0
            if(X7){
                if(x7_up == 0){
                    x7_up = 1;
                    do_plc_action(plc1, &plc_a_scan_y, PLC_ACTION_FLAG_LINK);
                }
            } else {
                x7_up = 0;
            }
            
            if(X9){
                if(x9_up == 0){
                    x9_up = 1;
                    do_plc_action(plc1, &plc_a_scan_y, PLC_ACTION_FLAG_UNLK);
                }
            } else {
                x9_up = 0;
            }
            
            if(X11){
                if(x11_up == 0){
                    x11_up = 1;
                    plc_out_y1 = !plc_out_y1;
                    do_plc_action(plc1, &plc_a_out_y1, PLC_ACTION_FLAG_ONCE);
                }
            } else {
                x11_up = 0;
            }
            #endif
            if(edge_dn(X7, x7_up)){
                do_plc_action(plc1, &plc_a_scan_y, PLC_ACTION_FLAG_LINK);
            }
            if(edge_dn(X9, x9_up)){
                do_plc_action(plc1, &plc_a_scan_y, PLC_ACTION_FLAG_UNLK);
            }
            if(edge_up(X12, x11_up)){
                plc_out_y1 = !plc_out_y1;
                do_plc_action(plc1, &plc_a_out_y1, PLC_ACTION_FLAG_ONCE);
            }
            if(edge_up(X18, x18_up)){
                dpc_for_test_speed/=2L;
                if(dpc_for_test_speed==0)dpc_for_test_speed=1;
                TimerSet(Timer_for_test, dpc_for_test_speed, TIMER_TYPE_AUTO, dpc_for_test, NULL);
            }
            if(edge_up(X20, x20_up)){
                dpc_for_test_speed*=2L;
                if(dpc_for_test_speed>100000)dpc_for_test_speed=100000;
                TimerSet(Timer_for_test, dpc_for_test_speed, TIMER_TYPE_AUTO, dpc_for_test, NULL);
            }
        
        }
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

void __far TaskDumpArp(void __far * data)
{
    INT16S  i;
    char buf[64];
    char icmp_data[]="jun send this icmp echo request packet to 192.168.0.22!!!";

    for(;;){/*lint --e{527}*/
        
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
            buf[STRLEN(buf)]=' ';
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
        TaskSleep(50L);
        send_echo(ICMP_ECHO, 0, 0, 0, (192L+ (168L<<8) + (0L<<16) + (22L<<24)), icmp_data, (INT16U)STRLEN(icmp_data));
    }
}


/*------------------------------------------------------------------------------------
* 函数: TaskTest()
* 说明: 测试任务
**----------------------------------------------------------------------------------*/
void __far TaskTest2(void __far * data)
{
/*lint --e{529}*/
    INT32U tdata;
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

    tdata=(INT32U)data;
    tdata+=1L;

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
void apical TaskSwitchHook(void)
{
}


INT16S send_msg=0;

BOOL msghdlr(HANDLE task, MSGCB __far * m)
{
    textprintstr(55, 21, "Message:", 0);
    textprintchar(64, 21, (INT08S)m->msg, 0);
    textprintdec32(73, 21, (INT32S)SecondsFromStart, 0, 0);
    send_msg=1;
    return ok;
}

void __far TaskSendMsg(void __far * data)
{
    MSGCB msg;

    InitMessage(&msg);

    lock_kernel();
    CurrentTCB->msg_handler = msghdlr;
    unlock_kernel();
    
    for(;;){
        if(send_msg){
            SendMessage(rcv_msg_handle, &msg);
            msg.msg++;
            send_msg=0;
        } else {
            TaskSleep(10L);
        }
    }
}

BOOL rx_msghdlr(HANDLE task, MSGCB __far * m)
{
    textprintstr(70, 23, "RX:", 0);
    textprintdec16(73, 23, m->msg, 0, 0);
    textprintdec32(73, 24, (INT32S)SecondsFromStart, 0, 0);
    return ok;
}


void __far rcv_msg(void __far * data)
{
    MSGCB msg;
    INT08U red=0, green=0, blue=0;
    textprintstr(55, 22, "rcv_msg start", 0);
    lock_kernel();
    CurrentTCB->msg_handler = rx_msghdlr;
    unlock_kernel();
    for(;;){
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

void exit_application(void)
{
    ExitApplication();
    clrscr();
}

void __far * mem_list[2048];

long get_free_mem(void)
{
    long mem;
    int i;

    mem = 0L;

    for(i=0; i<2048; i++)mem_list[i]=NULL;
    for(i=0; i<2048; i++){
        mem_list[i] = farmalloc(512uL);
        if(!mem_list[i])break;
        mem += 512;
    }

    for(i=0; i<2048; i++)if(mem_list[i])farfree(mem_list[i]);
    return mem;
}


/*====================================================================================
 * 
 * 本文件结束: start.c
 * 
**==================================================================================*/

