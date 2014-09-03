 #include "conio.h"
/* #include "graph.h"*/
typedef struct frame { int
                       lt,lb,rt,rb,
                       upline,
                       btline,
                       lside,
                       rside,
                       attr;
                     } FRAME;
/*typedef struct lastinfo{
        unsigned char winleft;
        unsigned char wintop;
        unsigned char winright;
        unsigned char winbottom;
        unsigned char attribute;
        unsigned char normattr;
        unsigned char currmode;
        unsigned char screenheight;
        unsigned char screenwidth;
        unsigned char curx;
        unsigned char cury;
};*/
typedef struct window {
                  int    left,
                         top,
                         right,
                         bottom;
                  FRAME  frame;    /* type of frame */
                  char   *buf,     /* background buffer */
                         *title;   /* TITLE string */
                  int    stat;     /* OPEN? CLOSE? OTHERS?*/
        struct text_info lastinfo; /* ���� info */
                      }  WINDOW;   /* �H�W���c��s WINDOW */
#define NO 0 /* �L  �� */
#define SS 1 /* ��u�� */
#define DD 2 /* ���u�� */
#define SD 3 /* �W�U��u�B���k���u */
#define DS 4 /* �W�U���u�B���k��u */
#define NORM   0x0700  /* ���`���r���ݩ�   */
#define REVE   0x7000  /* �ϥժ��r���ݩ�   */
#define HIGH   0x0f00  /* ���G�ת��r���ݩ� */

#define BLACK   0      /* ���`���r���ݩ� */
#define WHITE   7      /* �ϥժ��r���ݩ� */
#define HIGH   0x0f00 /* ���G�ת��r���ݩ� */

#define ED           printf("\x1b[2J")              /* erase display */
#define EL           printf("\x1b[K")               /* erase line    */
#define CUP(row,col) _settextposition(row,col)      /* position      */
#define CUU          printf("\x1b[A")               /* cursor up 1 row */
#define CUD          printf("\x1b[B")               /* cursor down 1 row */
#define CUF          printf("\x1b[C")               /* cursor forword 1 col */
#define CUB          printf("\x1b[D")               /* cursor ackword 1 col */

/* �H�U�� stat ���� */
#define  CLOSE 2
#define  OPEN  1

#define HOME 71
#define END  79
#define DEL  83
#define INS  82
#define FWD  77
#define BS   75

/* FUNCTION PROTOTYPE */
void   v_poke(unsigned int p, int x, int y, int attrib);
void   w_area(WINDOW *wnd);
void   w_frame(WINDOW *wnd);
WINDOW *w_creat(int left, int top, int right, int bottom,
                int frametype,int attr,char *title);
void   w_open(WINDOW *wnd);
void   w_close(WINDOW *wnd);
void   w_delete(WINDOW *wnd);
void   w_shadow(WINDOW *wnd,int low);

