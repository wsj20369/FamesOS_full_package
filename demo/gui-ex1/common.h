/*************************************************************************************
 * 文件: demo/common.h
 *
 * 说明: 演示头文件
 *
 * 作者: Jun
 *
 * 时间: 2010-12-17
*************************************************************************************/
#ifndef FAMES_DEMO_COMMON_H
#define FAMES_DEMO_COMMON_H

#include "C:\FamesOS\x\slc\core\core.h"
#include "config.h"

/*lint -e806*/

void __far TaskTest(void __far * data);
void __far TaskSendMsg(void __far * data);
void __far rcv_msg(void __far * data);
long       get_free_mem(void);

void       demo_init_plc(void);
void       demo_init_gui(void);
void       example_init_xms(void);
void       example_init_udp_port(void);
void       init_font(void);

void init_welcome_screen(void);
void welcome_start(void);
void welcome_ended(void);
void startup_message(INT08S __far * s);



#define  pause(ns)  ENTER_CRITICAL(); DELAY(ns); EXIT_CRITICAL();


struct plc_io_x_s{
    __int x0:1;
    __int x1:1;
    __int x2:1;
    __int x3:1;
    __int x4:1;
    __int x5:1;
    __int x6:1;
    __int x7:1;
    __int x8:1;
    __int x9:1;
    __int x10:1;
    __int x11:1;
    __int x12:1;
    __int x13:1;
    __int x14:1;
    __int x15:1;
    __int x16:1;
    __int x17:1;
    __int x18:1;
    __int x19:1;
    __int x20:1;
    __int x22:1;
    __int x23:1;
    __int x24:1;
    __int x25:1;
    __int x26:1;
    __int x27:1;
    __int x28:1;
    __int x29:1;
    __int x30:1;
    __int x31:1;
};

#ifndef DEMO_PLC_C
extern PLC __far * plc1;
extern INT16S r4151, plc_x[], plc_y[];
extern PLC_ACTION  plc_a_scan_y, plc_a_out_y1;
extern INT16S      plc_scan_y[], plc_out_y1;
extern struct plc_io_x_s __far * plc_io_x;
#endif

#define  X7  (plc_io_x->x7)    /* start scan y */
#define  X9  (plc_io_x->x9)    /* stop  scan y */
#define  X12 (plc_io_x->x12)   /* out y1 now   */
#define  X18 (plc_io_x->x18)   /* more speed   */
#define  X20 (plc_io_x->x20)   /* less speed   */

#endif /* #ifndef FAMES_DEMO_COMMON_H */

/*====================================================================================
 * 
 * 本文件结束: demo/common.h
 * 
**==================================================================================*/

