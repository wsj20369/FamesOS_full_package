/**************************************************************************************
 * 文件:    demo/demo.c
 *
 * 说明:    FONT功能演示
 *
 * 作者:    Jun
 *
 * 时间:    2010-12-30
**************************************************************************************/
#define  DEMO_FONT_C
#include <includes.h>
#include "common.h"


FONTINFO font_asc_16 = {NO, FONT_TYPE_ASCII,   0,  8, 16, 1,  0, "ASC16",    NULL};
FONTINFO font_hz_16  = {NO, FONT_TYPE_GB2312,  0, 16, 16, 2,  0, "HZK16",    NULL};
FONTINFO font_asc_48 = {NO, FONT_TYPE_ASCII,   0, 24, 48, 3, 32, "ASC48",   NULL};
FONTINFO font_asc_fs = {NO, FONT_TYPE_GB2312,  0, 24, 24, 3, 15*94 , "HZK24S", NULL};

void demo_init_font(void) 
{
    LoadFont(&font_asc_16);
    LoadFont(&font_hz_16);
    LoadFont(&font_asc_48);
    LoadFont(&font_asc_fs);

    RegisterFont(&font_hz_16, &font_asc_16);
    RegisterFont(NULL, &font_asc_48);
    RegisterFont(&font_asc_fs, NULL);
}

/*=====================================================================================
 * 
 * 本文件结束: demo/xms.c
 * 
**===================================================================================*/

