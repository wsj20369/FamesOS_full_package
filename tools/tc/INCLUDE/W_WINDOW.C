/*#include "window.h"
  #include "stdio.h"
  #include "conio.h"
  #include "dos.h"
  #include "malloc.h"
  #include "graph.h"*/

FRAME frameset[] = {
/*�L  ��*/            {00, 00, 00, 00, 00, 00, 00, 00, 0},
/*��u��*/            {218,192,191,217,196,196,179,179,0},
/*���u��*/            {201,200,187,188,205,205,186,186,0},
/*�W�U��u,���k���u*/ {214,211,183,189,196,196,186,186,0},
/*�W�U���u,���k��u*/ {213,212,184,190,205,205,179,179,0},
                   };    /* �аѷ� FRAME ���w�q */

/* ------------------------- */
/* --- FUNCTION v_poke() --- */
/* ------------------------- */

void v_poke( unsigned int p, int y, int x,int attrib)
     {
         int offset;
         int *buf1,buf[1];
         int width;
         buf1=buf;
         *buf1=(attrib|p);
         offset=(2* ((y-1)+(x-1)*80) );
         movedata(FP_SEG(buf1),FP_OFF(buf1),0xb000,offset,2);
     }

/* ------------------------- */
/* --- FUNCTION w_area() --- */
/* ------------------------- */

void w_area(WINDOW *wnd)
     {
       _settextwindow(wnd->top,wnd->left,wnd->bottom,wnd->right);
     }

/* ------------------------- */
/* --- FUNCTION w_creat() -- */
/* ------------------------- */

WINDOW *w_creat(int top, int left, int bottom, int right,
                int frametype,int attr,char *title)
{
      WINDOW *wnd;
      wnd = (WINDOW *) malloc(sizeof(WINDOW));
      wnd->left   = left;   /* set position of window */
      wnd->top    = top;
      wnd->right  = right;
      wnd->bottom = bottom;
      wnd->frame  = frameset[frametype]; /* struct �]�w */
      wnd->frame.attr = attr;
      wnd->buf    = NULL;
      wnd->title  = title;
      wnd->stat   = CLOSE;
      return (wnd);
}

/* -------------------------- */
/* -- FUNCTION  w_frame() --- */
/* ------------------------------------------------ */
/* draw window frame (startx,starty) to (endx,endy) */
/* ------------------------------------------------ */

void w_frame(WINDOW *wnd)
{
  register int  i;
  if((wnd->frame.lside == 00) && (wnd->frame.rside == 00))
      return;
  for ( i=wnd->left; i<=wnd->right; i++) {
       v_poke(wnd->frame.upline,i,wnd->top-1,
              wnd->frame.attr);
       v_poke(wnd->frame.btline,i,wnd->bottom+1,
              wnd->frame.attr);
    }
  if (wnd->title != NULL)
     for (i=0; i< strlen(wnd->title);i++)
     v_poke((int) *(wnd->title+i),(wnd->left+wnd->right-
            strlen(wnd->title))/2+i, wnd->top-1,REVE);
  for ( i=wnd->top; i<=wnd->bottom; i++) {
       v_poke(wnd->frame.lside, wnd->left-1, i,
              wnd->frame.attr);
       v_poke(wnd->frame.rside, wnd->right+1, i,
              wnd->frame.attr);
    }
  v_poke(wnd->frame.lt,wnd->left-1,wnd->top-1,
         wnd->frame.attr);
  v_poke(wnd->frame.lb,wnd->left-1,wnd->bottom+1,
         wnd->frame.attr);
  v_poke(wnd->frame.rt,wnd->right+1,wnd->top-1,
         wnd->frame.attr);
  v_poke(wnd->frame.rb,wnd->right+1,wnd->bottom+1,
         wnd->frame.attr);
}


/* ------------------------ */
/* --- FUNCTION w_open() -- */
/* ------------------------------------ */
/* --- w_open save window background, - */
/* --- open a window pointed by wnd   - */
/* ------------------------------------ */

void w_open(WINDOW *wnd)
{

  int  height, width;
     if (wnd->stat & OPEN) /* �w OPEN �h���A OPEN */
         return;
     height = wnd->bottom - wnd->top+3;
     width  = wnd->right - wnd->left+3;
     if ((wnd->buf=malloc(height*width*2)) ==NULL) {
          cputs("No space for buffer!");
          return;
      }
      w_frame(wnd);  /* �e������� */
      w_area(wnd);   /* ���w�b�o�ӵ�����Ū�g��� */
      wnd->stat |= OPEN;  /* �]���w OPEN ���A */
}


/*-----------------------------*/
/* --- FUNCTION w_close() -----*/
/*-----------------------------*/

void w_close(WINDOW *wnd)
{
  if (wnd->stat & OPEN) {  /* �w open ���~ close */
      free(wnd->buf);
      wnd->stat &= ~OPEN;
      _settextwindow(wnd->lastinfo.winleft,wnd->lastinfo.wintop,
             wnd->lastinfo.winright,wnd->lastinfo.winbottom);
    }
}

/*-----------------------------*/
/*--- FUNCTION  w_delete() --- */
/*-----------------------------*/

void w_delete(WINDOW *wnd)
  {
   /* if (wnd->stat & OPEN)
         w_close(wnd);     */
      free(wnd);
  }


/*-----------------------------*/
/* --- FUNCTION w_shadow()     */
/*-----------------------------*/
void w_shadow(WINDOW *wnd,int low)
 {
    int  addr,i;
    int  charattr;

    if (low) {
         for (i=wnd->left; i<= wnd->right+2; i++) {
              addr = ((wnd->bottom+1)*80+i)*2;
              charattr = peek(0xb000,addr);
              poke(0xb000, addr, charattr & 0xf7ff);
          }
         for (i=wnd->top-1; i<= wnd->bottom; i++) {
              addr = ((i)*80+wnd->right+1)*2;
              charattr = peek(0xb000,addr);
              poke(0xb000, addr, charattr & 0xf7ff);
              charattr = peek(0xb000,addr+2);
              poke(0xb000, addr+2, charattr & 0xf7ff);
          }
     }
    else {
         for (i=wnd->left; i<= wnd->right+2; i++) {
              addr = ((wnd->bottom+1)*80+i)*2;
              charattr = peek(0xb000,addr);
              poke(0xb000, addr, charattr | 0x0800);
          }
         for (i=wnd->top-1; i<= wnd->bottom; i++) {
              addr = ((i)*80+wnd->right+1)*2;
              charattr = peek(0xb000,addr);
              poke(0xb000, addr, charattr | 0x0800);
              charattr = peek(0xb000,addr+2);
              poke(0xb000, addr+2, charattr | 0x0800);
          }
     }
 }

