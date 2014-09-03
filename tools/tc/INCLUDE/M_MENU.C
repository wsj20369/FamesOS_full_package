

#include "dir.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "window.h"
#include "conio.h"

/* ********************************* */
/* *	    m_creat ( ) 	   * */
/* ********************************* */

MENU *m_creat(char **mtable,int color)
{
    MENU *menu;
    menu=(MENU *) malloc (sizeof(MENU));
    menu->mtable=mtable;
    menu->start=0;
    menu->now=0;
    menu->color=color;
    menu->x=1;
    menu->y=1;
    menu->nitem=0;
    while (menu->mtable[menu->nitem])
	   menu->nitem++;
    return menu;
}

/* ********************************* */
/* *	    m_gotoxy ( )	   * */
/* ********************************* */
/* *	  #include "window.h"      * */
/* *	  #include "conio.h"       * */
/* ********************************* */

void m_gotoxy(MENU *menu,WINDOW *wnd,int x,int y)
 {
    int  ncol,wcol;
    wcol = strlen(menu->mtable[0])+1;
    ncol=(wnd->right-wnd->left+1)/wcol;
    textcolor(menu->color);
    textbackground(menu->color == WHITE ? BLACK : WHITE);
    gotoxy((menu->x-1)*wcol+2,menu->y);
    cputs(menu->mtable[menu->now]);
    menu->x=x;
    menu->y=y;
    menu->now=menu->start+(y-1)*ncol+x-1;
    textcolor(menu->color==WHITE ? BLACK : WHITE);
    textbackground(menu->color);
    gotoxy((x-1)*wcol+2,y);
    cputs(menu->mtable[menu->now]);
    textcolor(menu->color);
    textbackground(menu->color == WHITE ? BLACK : WHITE);
}

/* ************************************************* */
/* *	    m_list ( )				   * */
/* ************************************************* */
/* *						   * */
/* *  Fill a MENU into WINDOW			   * */
/* *  m_list() 把 menu 的內容列出在 window 內	   * */
/* *  由 menu->now 所指的項目開始, 列滿一個 window * */
/* *  若不滿一個 window 則填空。		   * */
/* *	 #include "window.h"                       * */
/* ************************************************* */

void m_list(MENU *menu,WINDOW *wnd)
{
  char str[80];
  int row, col, i, j, wcol;
  wcol = strlen(menu->mtable[0])+1;
  row = 0;
  j = 0;
  clrscr();
  while(++row <= (wnd->bottom - wnd->top + 1)) {
      col = 0;
      while(++col <= (wnd->right-wnd->left+1)/wcol) {
	    gotoxy((col-1)*(wcol) + 2,row);
	    if(j < menu->nitem)
		 cputs(menu->mtable[j++]);
	 }
    }
    m_gotoxy(menu,wnd,menu->x,menu->y);
  }


/* ********************************* */
/* *	    m_pick ( )		   * */
/* ************************************* */
/* *  Move menu bar & Pick a MENU item * */
/* *	   #include "window.h"         * */
/* *	   #include "conio.h"          * */
/* ************************************* */

int m_pick(MENU *menu,WINDOW *wnd)
{
  int ncol,	 /* number of column */
      nrow,	 /* number of row */
      last_x,
      last_y;
  int c, wcol;
  wcol=strlen(menu->mtable[0])+1;
  ncol=((wnd->right-wnd->left)+1)/wcol;  /* 行數 */
  nrow=(wnd->bottom-wnd->top)+1;
  last_y = (menu->nitem-1) / ncol+1;
  last_x = (menu->nitem-1) % ncol+1;
  w_open(wnd);
  textcolor(menu->color);
  textbackground(menu->color==WHITE ? BLACK : WHITE);
 /*u_shape(15,15);*/

  m_list(menu,wnd);

  while(1) {

    while(bioskey(1)==0);
    c=bioskey(0);

    switch(c>>=8) {
      case 72: if(menu->y > 1)		   /* up */
		  m_gotoxy(menu,wnd, menu->x, menu->y-1); /*游標上移*/
	       else if (menu->now == 0 && ncol == 1)	  /*單行則繞捲*/
		  m_gotoxy(menu,wnd, menu->x, menu->nitem);
		break;
      case 80: if((menu->y < last_y) &&    /* down */
		 (menu->nitem-menu->now>ncol))
		  m_gotoxy(menu,wnd, menu->x, menu->y+1); /*游標下移*/
	       else if (menu->y == last_y && ncol == 1)   /*單行則繞捲*/
		  m_gotoxy(menu,wnd,menu->x,1);
		break;
      case  75: if(menu->x > 1) 	   /* left */
		  m_gotoxy(menu,wnd, menu->x-1, menu->y); /*游標左移*/
		else if (menu->now == 0 && nrow == 1)	  /*單列則繞捲*/
		  m_gotoxy(menu,wnd, menu->nitem, menu->y);
		break;
      case  77: if(menu->x < ncol && menu->now<menu->nitem-1) /* right */
		  m_gotoxy(menu,wnd, menu->x+1, menu->y); /*游標右移*/
		else if (menu->x == last_x && nrow == 1)  /*單列則繞捲*/
		  m_gotoxy(menu,wnd,1,menu->y);
		break;
      case  71: 			   /* home */
		m_gotoxy(menu,wnd,1,1);
		break;
      case  79: 				     /* end */
		m_gotoxy(menu,wnd,last_x,last_y);
		break;
      case  28: 				     /* return */
		return (menu->now);
      case  1:					    /* escape */
		w_close(wnd);
	  /*	cu_shape(11,12);  */
		return (-1);
      }
    }
  }

