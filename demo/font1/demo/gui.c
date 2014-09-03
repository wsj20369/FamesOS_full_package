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

gui_control __far * root1, __far * root2;
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

void gui_keyhook(KEYCODE key)
{
    switch(key){
        case F1:
            gui_set_root_control(root1);
            break;
        case F2:
            gui_set_root_control(root2);
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
            gui_set_control_style(root1, style);
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

/******************/
void sys_monitor_ctrl_draw(gui_control __far * c)
{
    INT32S s[12];
    INT08S str[512];
    __int  i, x, y, x1, y1;

    x  = c->real_rect.x + 1;
    y  = c->real_rect.y + 1;
    x1 = c->real_rect.width + x - 2;
    y1 = c->real_rect.height + y - 2;

    if(c->flag & GUI_CTRL_FLAG_REFRESH){
        sprintf(str, "System Monitor");
        DrawFont(x+150, y, str, c->color, 2,  DRAW_OPT_FIL_BG);
        y += 56;
        sprintf(str, "handle  buf        btm        ptr          total    used     remain   state   prio   name ");
        DrawFont(x, y, str, c->color, 0,  DRAW_OPT_FIL_BG);
        y += 14;
        sprintf(str, "------------------------------------------------------------------------------------------");
        DrawFont(x, y, str, c->color, 0,  DRAW_OPT_FIL_BG);
        y += 14;
        for(i=0; i<MAX_TASKS; i++){
            if(TCBS[i].TcbUsed != TCB_USED_YES)continue;
            s[0] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_GET_BUF);
            s[1] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_GET_BTM);
            s[2] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_GET_PTR);
            s[3] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_TOTAL);
            s[4] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_USED);
            s[5] = (INT32S)TaskStackCheck(i, STACK_CHECK_OPT_REMAIN);
            sprintf(str, "  %2d    %p  %p  %p    %-6ld   %-6ld %c %-6ld   %s   %-6d %s", 
                         i, s[0], s[1], s[2], s[3], s[4], ((s[5]<32L)?'*':' '), s[5], 
                         ((TCBS[i].TaskState==0)?"     ":"SLEEP"),
                         TCBS[i].Priority, TCBS[i].TaskName);/*lint !e559 !e622*/
            DrawFont(x, y, str, c->color, 0,  DRAW_OPT_FIL_BG);
            y += 14;
        }
        if(1){
            char aaa[32];
            sprintf(aaa, "CPU使用率: %3d%%", CPU_USED);
            DrawFont(x, y, aaa, 0, 0, DRAW_OPT_FIL_BG);
        }
        y+=14;
        sprintf(str, "tasks: %-4d free-memory: %-8ld  switches: %-8ld  seconds-from-start: %ld",
                     NumberOfTasks, get_free_mem(), TaskSwitches, SecondsFromStart);
        DrawFont(x, y, str, c->color, 0,  DRAW_OPT_FIL_BG);
        y += 14;
        sprintf(str, "------------------------------------------------------------------------------------------");
        DrawFont(x, y, str, c->color, 0,  DRAW_OPT_FIL_BG);
        y += 24;
        sprintf(str, "FamesOS "FamesOS_VersionString);
        DrawFont(x, y, str, 68, 2,  DRAW_OPT_FIL_BG);
        y += 50;
        sprintf(str, "我是中国人,hello, I am a chinese!");
        DrawFont(x, y, str, 98, 1,  DRAW_OPT_FIL_BG);
        DrawFont(x, y+16, str, 98, 0,  DRAW_OPT_FIL_BG);
        y += 50;
    }
}
gui_control_type sys_monitor_type = {0, sys_monitor_ctrl_draw};
__int            sys_monitor_id;

gui_control __far * sys_monitor;
    
/******************/
BMPINFO info[6];

void demo_init_gui(void)
{
    demo_init_font();

    my_ctrl_id=gui_register_usr_ctrl(&my_control_type);
    sys_monitor_id = gui_register_usr_ctrl(&sys_monitor_type);

    root1 = gui_create_control(GUI_CTRL_FORM, 60, 100, 800, 500, 3, 0, 0, 0);    
    if(!root1)return;

    root2 = gui_create_control(GUI_CTRL_FORM, 100, 200, 800, 368, 5, 0, 0, 0);
    if(!root2)return; 

    form1 = gui_create_control(GUI_CTRL_FORM, 180, 50, 320, 82, 5, 0, 0, FORM_STYLE_XP_BORDER);
    if(!form1)return; 

    label1 = gui_create_control(GUI_CTRL_LABEL, 50, 50, 100, 32, 7, 0, 0, LABEL_STYLE_BORDER);
    if(!label1)return; 
    gui_label_init_private(label1, 32);
    gui_label_set_text(label1, "this is a label!");

    edit1 = gui_create_control(GUI_CTRL_EDIT, 50, 100, 100, 32, 9, 0, 0, 0);
    gui_edit_init_private(edit1, 32);
    gui_edit_set_text(edit1, "this is a edit!");
    if(!edit1)return; 

    button1 = gui_create_control(GUI_CTRL_BUTTON, 3, 3, 314, 32, 9, 0, 0, 0);
    if(!button1)return;
   
    progress1 = gui_create_control(GUI_CTRL_PROGRESS, 50, 150, 700, 32, 0, 0, 0, 0);
    if(!progress1)return; 
    gui_set_control_associated(progress1, &assoc1, 0);
    gui_progress_init_private(progress1);

    my_control = gui_create_control(my_ctrl_id, 0, 0, 0, 0, 0, 0, 0, 0);
    if(!my_control)return;

    sys_monitor = gui_create_control(sys_monitor_id, 30, 6, 10, 10, 0, 0, 0, 0);
    if(!sys_monitor)return;

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

    gui_control_link(root1, sys_monitor);

    gui_control_link(root2, form1);
    gui_control_link(root2, my_control);
    gui_control_link(root2, label1);
    gui_control_link(root2, edit1);
    gui_control_link(form1, button1);
    gui_control_link(root2, progress1);
    gui_control_link(root2, pic1);

    RegisterKeyHook(gui_keyhook);

    #if 0
    printf("root1-1: %d, %d, %d, %d, %d\n",
        root1->rect.x,
        root1->rect.y,
        root1->rect.width,
        root1->rect.height,
        root1->color);
    printf("root1-2: %d, %d, %d, %d, %d\n",
        root1->real_rect.x,
        root1->real_rect.y,
        root1->real_rect.width,
        root1->real_rect.height,
        root1->color);
    printf("root2-1: %d, %d, %d, %d, %d\n",
        root2->rect.x,
        root2->rect.y,
        root2->rect.width,
        root2->rect.height,
        root2->color);
    printf("root2-2: %d, %d, %d, %d, %d\n",
        root2->real_rect.x,
        root2->real_rect.y,
        root2->real_rect.width,
        root2->real_rect.height,
        root2->color);
    printf("label1-1: %d, %d, %d, %d, %d\n",
        label1->rect.x,
        label1->rect.y,
        label1->rect.width,
        label1->rect.height,
        label1->color);
    printf("label1-2: %d, %d, %d, %d, %d\n",
        label1->real_rect.x,
        label1->real_rect.y,
        label1->real_rect.width,
        label1->real_rect.height,
        label1->color);
    getch();
    #endif

    StartGUI();
    gui_set_root_control(root1);
    return;
}


/*=====================================================================================
 * 
 * 本文件结束: demo/gui.c
 * 
**===================================================================================*/

