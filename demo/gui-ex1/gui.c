/**************************************************************************************
 * 文件:    demo/gui.c
 *
 * 说明:    GUI功能演示
 *
 * 作者:    Jun
 *
 * 时间:    2010-12-18
**************************************************************************************/
#define  DEMO_GUI_C
#include <includes.h>
#include "common.h"

gui_control __far * root1, __far * root2, __far * about_system_root;
gui_control __far * label1;
gui_control __far * edit1;
gui_control __far * button1;
gui_control __far * progress1;
gui_control __far * form1;
gui_control __far * pic1;

progress_assoc_t assoc1={0,0};

RECT  rect1={100,100,100,32};

unsigned __int bbb_1[10]={0,};
unsigned __int bbb_2[10]={1,2,4,8,16,32,64,128,256,512};
unsigned __int style=0;

extern gui_control __far * welcome_root;

void gui_keyhook(KEYCODE key)
{
    switch(key){
        case F1:
            gui_set_root_control(root1);
            break;
        case F2:
            gui_set_root_control(root2);
            break;
        case F3:
            gui_set_root_control(welcome_root);
            break;
        case F4:
            gui_set_root_control(about_system_root);
            break;
        case LEFT:
            gui_move_control_left(root2, 1);
            break;
        case RIGHT:
            gui_move_control_right(root2, 1);
            break;
        case CTRL_LEFT:
            gui_move_control_left(root2, 30);
            break;
        case CTRL_RIGHT:
            gui_move_control_right(root2, 30);
            break;
        case UP:
            gui_move_control_up(root2, 11);
            break;
        case DOWN:
            gui_move_control_down(root2, 12);
            break;
        case 'Q': case 'q':
            QuitGUI();
            break;
        case '+':
            gui_set_control_higher(progress1, 1);
            break;
        case '-':
            gui_set_control_higher(progress1, -1);
            break;
        case 'a':
            gui_move_control_left(pic1, 7);
            break;
        case 'd':
            gui_move_control_right(pic1, 9);
            break;
        case 'w':
            gui_move_control_up(pic1, 7);
            break;
        case 's':
            gui_move_control_down(pic1, 9);
            break;
        default:
            if(key < '0' || key > '9')
                break;
            key-='0';
            if(!bbb_1[key]){
                style |=  bbb_2[key];
            } else {
                style &= ~bbb_2[key];
            }
            bbb_1[key]=!bbb_1[key];
            gui_set_control_style(label1, style);
            gui_set_control_style(edit1, style);
            gui_set_control_style(button1, style);
            gui_set_control_style(progress1, style);
            gui_set_control_style(root2, style);
            gui_set_control_style(pic1, style);
            break;
    }
}

__int abcde = 0;

void my_ctrl_draw(gui_control __far * c)
{
    static __int i=0, ii=0;

    if(++i>0){
        i=0;
        ii += 3;
        if(ii>100)
            ii=0;
        abcde = ii;
        /*
        printf("seconds = %8ld\n", SecondsFromStart);
        */
    }
}

gui_control_type my_control_type = {0, my_ctrl_draw};
__int            my_ctrl_id = 0;

gui_control __far * my_control;

gui_control __far * sys_monitor;
    
/******************/
BMPINFO info[6];

void demo_init_gui(void)
{
    init_font();


    root1 = gui_create_control(GUI_CTRL_FORM, 6, 6, 1012, 756, 3, 0, 0, FORM_STYLE_XP_BORDER);    
    if(!root1)return;
    gui_form_init_private(root1, 32);
    gui_form_set_caption(root1, "Root1");

    root2 = gui_create_control(GUI_CTRL_FORM, 400, 360, 560, 345, 8, 64, 0, 0);
    if(!root2)return; 
    gui_form_init_private(root2, 32);
    gui_form_set_caption(root2, "Root2");

    form1 = gui_create_control(GUI_CTRL_FORM, 180, 50, 320, 82, 5, 0, 0, FORM_STYLE_XP_BORDER);
    if(!form1)return; 
    gui_form_init_private(form1, 32);
    gui_form_set_caption(form1, "Form1");

    label1 = gui_create_control(GUI_CTRL_LABEL, 50, 50, 100, 32, 4, 0, 0, LABEL_STYLE_BORDER);
    if(!label1)return; 
    gui_label_init_private(label1, 32);
    gui_label_set_text(label1, "标签");

    edit1 = gui_create_control(GUI_CTRL_EDIT, 50, 100, 100, 32, 9, 0, 0, 0);
    gui_edit_init_private(edit1, 32);
    gui_edit_set_text(edit1, "this is a edit!");
    if(!edit1)return; 

    button1 = gui_create_control(GUI_CTRL_BUTTON, 3, 3, 314, 32, 9, 0, 0, 0);
    if(!button1)return;
   
    progress1 = gui_create_control(GUI_CTRL_PROGRESS, 50, 150, 420, 32, 1, 0, 0, 0);
    if(!progress1)return; 
    gui_set_control_associated(progress1, &assoc1, 0);
    gui_progress_init_private(progress1);

    my_control = gui_create_control(my_ctrl_id, 0, 0, 0, 0, 0, 0, 0, 0);
    if(!my_control)return;

    about_system_root = gui_create_control(GUI_CTRL_FORM, 6, 6, 1012, 756, 3, 0, 0, FORM_STYLE_XP_BORDER);  
    if(!about_system_root)return;
    gui_form_init_private(about_system_root, 32);
    gui_form_set_caption(about_system_root, "about_system_root");
    
    sys_monitor = gui_create_control(GUI_CTRL_SYS_MNTR, 16, 16, 1, 1, 0, 0, 0, SYS_MNTR_STYLE_STATIC_BDR|SYS_MNTR_STYLE_NO_BORDER);
    if(!sys_monitor)return;
    gui_sys_mntr_init_private(sys_monitor);

    pic1 = gui_create_control(GUI_CTRL_PICTURE, 50, 200, 150, 100, 0, 0, 0, 0);
    gui_picture_init_private(pic1);
    if(1){
        InitBMPINFO(&info[0]);
        LoadBmp(&info[0], "demo.bmp");
        InitBMPINFO(&info[1]);
        LoadBmp(&info[1], "demo1.bmp");
        InitBMPINFO(&info[2]);
        LoadBmp(&info[2], "demo2.bmp");
        InitBMPINFO(&info[3]);
        LoadBmp(&info[3], "demo3.bmp");
        InitBMPINFO(&info[4]);
        LoadBmp(&info[4], "demo4.bmp");
        InitBMPINFO(&info[5]);
        LoadBmp(&info[5], "demo5.bmp");
        gui_picture_set_picture(pic1, &info);
    }
        
    gui_control_link(NULL, root1);
    gui_control_link(NULL, root2);

    gui_control_link(about_system_root, sys_monitor);
    
    gui_control_link(root2, form1);
    gui_control_link(root2, my_control);
    gui_control_link(root2, label1);
    gui_control_link(root2, edit1);
    gui_control_link(form1, button1);
    gui_control_link(root2, progress1);
    gui_control_link(root2, pic1);

    RegisterKeyHook(gui_keyhook);

    init_welcome_screen();

    StartGUI();
    return;
}


/*=====================================================================================
 * 
 * 本文件结束: demo/gui.c
 * 
**===================================================================================*/

