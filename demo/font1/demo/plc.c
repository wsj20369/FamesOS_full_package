/**************************************************************************************
 * 文件:    demo/plc.c
 *
 * 说明:    PLC功能演示
 *
 * 作者:    Jun
 *
 * 时间:    2010-12-18
**************************************************************************************/
#define  DEMO_PLC_C
#include <includes.h>
#include "common.h"


PLC __far * plc1 = NULL;


INT16S r4151=0, plc_x[2]={0}, plc_y[2]={0};
void plc_x_finish(__int value);

BEGIN_PLC_ACTION_MAP(plc_a_1)
PLC_MAP_LINK("R04151", &r4151, 1, FATEK_PLC_READ_R, 10, NULL)
PLC_MAP_LINK("WX0000",  plc_x, 2, FATEK_PLC_READ_R,  0, plc_x_finish)
PLC_MAP_LINK("WY0000",  plc_y, 2, FATEK_PLC_READ_R,  0, NULL)
END_PLC_ACTION_MAP();

struct plc_io_x_s __far * plc_io_x;


PLC_ACTION  plc_a_scan_y, plc_a_out_y1;
INT16S      plc_scan_y[2]={0}, plc_out_y1=0;


void plc_x_finish(__int value)
{
    static __int good=0, bad=0;
    
    if(value)good++;
    else     bad++;
    textprintdec16(2, 15, good, 0, 0);
    textprintdec16(8, 15, bad, 0, 0);
}

void demo_init_plc(void)
{
    BOOL        retval;

    plc_io_x = (struct plc_io_x_s __far *)plc_x;
    
    plc1 = plc_alloc();

    if(!plc1)
        goto out;

    retval = plc_set_param( plc1,
                PLC_TYPE_FATEK,
                "fatek-plc-1",
                NULL,
                1,
                0x3F8,
                4,
                38400L,
                COM_PARITY_EVEN,
                7,
                1,
                COM_FIFO_TL_4
               );
    if(!retval)
        goto out2;

    retval = open_plc(plc1);

    if(!retval) 
        goto out2;

    retval = do_plc_action_map(plc1, plc_a_1);
    if(!retval)
        goto out1;
    
    retval = plc_set_action(&plc_a_scan_y,
                FATEK_PLC_WRITE_R,
                "WY0000",
                &plc_scan_y[0],
                2,
                10, /* 1 second */
                NULL
               );
    if(!retval)
        goto out1;
    
    retval = plc_set_action(&plc_a_out_y1,
                FATEK_PLC_WRITE_M,
                "Y0015",
                &plc_out_y1,
                2,
                0, /* as fast as possible */
                NULL
               );
    if(!retval)
        goto out1;    

out:
    return;
    
out1:
    (void)shut_plc(plc1);
out2:
    (void)plc_free(plc1);
    goto out;    
}


/*=====================================================================================
 * 
 * 本文件结束: demo/plc.c
 * 
**===================================================================================*/

