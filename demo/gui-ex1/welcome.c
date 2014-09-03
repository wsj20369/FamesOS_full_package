/*************************************************************************************
 * 文件:    slc/welcome.c
 *
 * 说明:    欢迎界面
 *
 * 作者:    Jun
 *
 * 时间:    2011-2-19
*************************************************************************************/
#define  SLC_WELCOME_C
#include <includes.h>

/*------------------------------------------------------------------------------------
 * 
 *  启始画面中的控件
 * 
**----------------------------------------------------------------------------------*/
gui_control __far * welcome_root;   /* 欢迎界面的主控件 */
gui_control __far * welcome_tupian;
gui_control __far * welcome_msg;
gui_control __far * welcome_status_bar;
gui_control __far * welcome_button1, __far * welcome_button2;

static char * welcome_filename = "welcome.bmp";
static char * kadar_icon_fname = "kd-icon.bmp";
static BMPINFO welcome_picture, kadar_icon;

/*------------------------------------------------------------------------------------
 * 函数:    startup_init()
 *
 * 描述:    启始初始化, 用于打开系统相关的一些资源
**----------------------------------------------------------------------------------*/
void init_welcome_screen(void)
{
    char __version[100];

    sprintf(__version, "Base: %s-%s   App: %s", 
                        os_get_name(),
                        os_get_version_string(),
                        "SLC-0.0.1");

    welcome_root       = gui_create_control(GUI_CTRL_FORM,    1,   1,  1021, 765, 0, 0, 0, FORM_STYLE_XP_BORDER|FORM_STYLE_TITLE);
    welcome_tupian     = gui_create_control(GUI_CTRL_PICTURE, 71,  70,  880, 450, 0, 0, 0, PICTURE_STYLE_NO_BORDER);
    welcome_msg        = gui_create_control(GUI_CTRL_LABEL,   7,   725,1006, 30,  0, 0, 1, LABEL_STYLE_CLIENT_BDR);
    welcome_button1    = gui_create_control(GUI_CTRL_BUTTON,  236, 590, 180, 42,  0, 0, 1, BUTTON_STYLE_FOCUS_BORDER | BUTTON_STYLE_CLIENT_BDR);
    welcome_button2    = gui_create_control(GUI_CTRL_BUTTON,  585, 590, 180, 42,  0, 0, 1, BUTTON_STYLE_CLIENT_BDR);
    welcome_status_bar = gui_create_control(GUI_CTRL_LABEL,   8,   706, 900, 20,  4, 0, 0, 0);
    if(!welcome_root ||
       !welcome_tupian ||
       !welcome_msg ||
       !welcome_button1 ||
       !welcome_button2 ||
       !welcome_status_bar){
        sys_print("init_welcome_screen(): failed to create controls for welcome!\n");
        exit_application();
    }
    gui_control_link(NULL, welcome_root);
    InitBMPINFO(&kadar_icon);
    LoadBmp(&kadar_icon, kadar_icon_fname);
    gui_form_init_private(welcome_root, 64);
    gui_form_set_icon(welcome_root, &kadar_icon);
    gui_form_set_caption(welcome_root, "欢迎使用本公司的产品 - 卡达电脑");

    gui_control_link(welcome_root, welcome_msg);
    gui_label_init_private(welcome_msg, 100);  /* 最多50个汉字 */
    
    gui_control_link(welcome_root, welcome_tupian);
    gui_picture_init_private(welcome_tupian);
    InitBMPINFO(&welcome_picture);
    LoadBmp(&welcome_picture, welcome_filename);
    gui_picture_set_picture(welcome_tupian, &welcome_picture);
    
    gui_control_link(welcome_root, welcome_button1);
    gui_button_init_private(welcome_button1, 32);
    gui_button_set_caption(welcome_button1, "启动中, 请稍请...");
        
    gui_control_link(welcome_root, welcome_button2);
    gui_button_init_private(welcome_button2, 32);
    gui_button_set_caption(welcome_button2, "[ESC] 退出");

    gui_control_link(welcome_root, welcome_status_bar);
    gui_label_init_private(welcome_status_bar, 100);
    gui_label_set_text(welcome_status_bar, __version);
}

void welcome_start(void)
{
    gui_set_root_control(welcome_root);
}

void welcome_ended(void)
{
    KEYCODE key;
    int     enter;
    int     pressed;
    INT16U  style;

    enter = 1;
    pressed = 1;

    gui_button_set_caption(welcome_button1, "[ENTER] 确定");

    for(;;){
        key = waitkey(0L);
        switch(key){
            case ENTER:
                if(enter)
                    goto out;
                else
                    exit_application();
                break;
            case ESC:
                exit_application();
                break;
            case LEFT:
                if(enter)
                    continue;
                enter = 1;
                break;
            case RIGHT:
                if(!enter)
                    continue;
                enter = 0;
                break;
            case TAB:
                enter = !enter;
                break;
            default:
                continue;
        }
        if(pressed)
            style = BUTTON_STYLE_PRESSED;
        else 
            style = 0;
        if(enter){
            gui_set_control_style(welcome_button1, BUTTON_STYLE_FOCUS_BORDER | BUTTON_STYLE_CLIENT_BDR | style);
            gui_set_control_style(welcome_button2, BUTTON_STYLE_CLIENT_BDR);
        } else {
            gui_set_control_style(welcome_button2, BUTTON_STYLE_FOCUS_BORDER | BUTTON_STYLE_CLIENT_BDR | style);
            gui_set_control_style(welcome_button1, BUTTON_STYLE_CLIENT_BDR);
        }
    }
    
out:
    return;
}

void startup_message(INT08S __far * s)
{
    char a[80];
    
    if(!welcome_msg || !s)
        return;
    sprintf(a, ">>>%s", s);
    gui_label_set_text(welcome_msg, a);
    TaskSleep(10L);
}


/*====================================================================================
 * 
 * 本文件结束: slc/welcome.c
 * 
**==================================================================================*/


