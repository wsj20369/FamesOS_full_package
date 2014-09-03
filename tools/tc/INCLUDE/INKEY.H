
/*
  ┌──────────────────────────┐
  │  書名 :   TURBO C 通訊程式設計 ----技巧與實務      │
  │  作者 :   楊玄周 楊玄彰                            │
  │  出版 :   波全資訊股份有限公司                     │
  └──────────────────────────┘
*/
#define   BACK_SPACE   0x08
#define   TAB          0x09
#define   ESC          0x1B

#define   CTRL_A       0x01
#define   CTRL_B       0x02
#define   CTRL_C       0x03
#define   CTRL_D       0x04
#define   CTRL_E       0x05
#define   CTRL_F       0x06
#define   CTRL_G       0x07
#define   CTRL_H       0x08
#define   CTRL_I       0x09
#define   CTRL_J       0x0A
#define   CTRL_K       0x0B
#define   CTRL_L       0x0C
#define   CTRL_M       0x0D
#define   CTRL_N       0x0E
#define   CTRL_O       0x0F
#define   CTRL_P       0x10
#define   CTRL_Q       0x11
#define   CTRL_R       0x12
#define   CTRL_S       0x13
#define   CTRL_T       0x14
#define   CTRL_U       0x15
#define   CTRL_V       0x16
#define   CTRL_W       0x17
#define   CTRL_X       0x18
#define   CTRL_Y       0x19
#define   CTRL_Z       0x1A

#define   RETURN       0xD
#define   HOME         0x4700
#define   END          0x4F00
#define   PGUP         0x4900
#define   PGDN         0x5100
#define   UP           0x4800
#define   DOWN         0x5000
#define   RIGHT        0x4D00
#define   LEFT         0x4B00
#define   SHIFT_TAB    0x0F00
#define   INS          0x5200
#define   DEL          0x5300

#define   CTRL_HOME    0x7700
#define   CTRL_END     0x7500
#define   CTRL_PGUP    0x8400
#define   CTRL_PGDN    0x7600
#define   CTRL_RIGHT   0x7400
#define   CTRL_LEFT    0x7300

#define   ALT_1       0x7800
#define   ALT_2       0x7900
#define   ALT_3       0x7A00
#define   ALT_4       0x7B00
#define   ALT_5       0x7C00
#define   ALT_6       0x7D00
#define   ALT_7       0x7E00
#define   ALT_8       0x7F00
#define   ALT_9       0x8000
#define   ALT_0       0x8100
#define   ALT_MINUS   0x8200
#define   ALT_EQUAL   0x8300

#define   ALT_Q       0x1000
#define   ALT_W       0x1100
#define   ALT_E       0x1200
#define   ALT_R       0x1300
#define   ALT_T       0x1400
#define   ALT_Y       0x1500
#define   ALT_U       0x1600
#define   ALT_I       0x1700
#define   ALT_O       0x1800
#define   ALT_P       0x1900

#define   ALT_A       0x1E00
#define   ALT_S       0x1F00
#define   ALT_D       0x2000
#define   ALT_F       0x2100
#define   ALT_G       0x2200
#define   ALT_H       0x2300
#define   ALT_J       0x2400
#define   ALT_K       0x2500
#define   ALT_L       0x2600

#define   ALT_Z       0x2C00
#define   ALT_X       0x2D00
#define   ALT_C       0x2E00
#define   ALT_V       0x2F00
#define   ALT_B       0x3000
#define   ALT_N       0x3100
#define   ALT_M       0x3200

#define   F1           0x3B00
#define   F2           0x3C00
#define   F3           0x3D00
#define   F4           0x3E00
#define   F5           0x3F00
#define   F6           0x4000
#define   F7           0x4100
#define   F8           0x4200
#define   F9           0x4300
#define   F10          0x4400

#define   CTRL_F1      0x5E00
#define   CTRL_F2      0x5F00
#define   CTRL_F3      0x6000
#define   CTRL_F4      0x6100
#define   CTRL_F5      0x6200
#define   CTRL_F6      0x6300
#define   CTRL_F7      0x6400
#define   CTRL_F8      0x6500
#define   CTRL_F9      0x6600
#define   CTRL_F10     0x6700

#define   SHIFT_F1     0x5400
#define   SHIFT_F2     0x5500
#define   SHIFT_F3     0x5600
#define   SHIFT_F4     0x5700
#define   SHIFT_F5     0x5800
#define   SHIFT_F6     0x5900
#define   SHIFT_F7     0x5A00
#define   SHIFT_F8     0x5B00
#define   SHIFT_F9     0x5C00
#define   SHIFT_F10    0x5D00

#define   ALT_F1       0x6800
#define   ALT_F2       0x6900
#define   ALT_F3       0x6A00
#define   ALT_F4       0x6B00
#define   ALT_F5       0x6C00
#define   ALT_F6       0x6D00
#define   ALT_F7       0x6E00
#define   ALT_F8       0x6F00
#define   ALT_F9       0x7000
#define   ALT_F10      0x7100

/* charater definition */
#define   CarriageReturn  '\r'
#define   LineFeed        '\n'
#define   SPACE           ' '

int     inkey( void );
void    kbflush( void );
