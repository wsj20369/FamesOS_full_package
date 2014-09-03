/**************************************************************************************
 * 文件:    slc/font.c
 *
 * 说明:    SLC中用到的字体
 *
 * 作者:    Jun
 *
 * 时间:    2011-3-3
**************************************************************************************/
#define  SLC_FONT_C
#include <includes.h>
#include "common.h"


FONTINFO font_asc_16 = {NO, FONT_TYPE_ASCII,   0,  8, 16, 1,  0, "ASC16",    NULL};
FONTINFO font_hz_16  = {NO, FONT_TYPE_GB2312,  0, 16, 16, 2,  0, "HZK16",    NULL};
FONTINFO font_asc_48 = {NO, FONT_TYPE_ASCII,   0, 24, 48, 3, 32, "ASC48",   NULL};
FONTINFO font_asc_fs = {NO, FONT_TYPE_GB2312,  0, 24, 24, 3, 15*94 , "HZK24F", NULL};
FONTINFO font_hz_20s = {NO, FONT_TYPE_GB2312,  0, 20, 20, 3, 0 , "HZK20S", NULL};

int font16, font48, font24, font20;

void init_font(void) 
{
    load_font(&font_asc_16);
    load_font(&font_hz_16);
    load_font(&font_asc_48);
    load_font(&font_asc_fs);
    load_font(&font_hz_20s);

    font16=register_font(&font_hz_16, &font_asc_16);
    font48=register_font(NULL, &font_asc_48);
    font24=register_font(&font_asc_fs, NULL);
    font20=register_font(&font_hz_20s, NULL);
}
/*=====================================================================================
 * 
 * 本文件结束: slc/font.c
 * 
**===================================================================================*/

