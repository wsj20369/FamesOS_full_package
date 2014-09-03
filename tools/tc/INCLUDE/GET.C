
extern WINDOW *wnd3;
extern int w_gets();
extern int s_gets();
extern void w_poke();
extern void s_poke();
/* ------------------------- */
/* --- FUNCTION w_poke() --- */
/* - < for window filed > -- */
/* ------------------------- */
void w_poke( unsigned int p, int x, int y,int attrib)
     {
         int offset;
         int *buf1,buf[1];
         int width;
         buf1=buf;
         *buf1=(attrib|p);
         width=(wnd3->right-wnd3->left)+1;
         offset=(2* (((y-1)+(wnd3->left-1))+((x-1)+(wnd3->top-1))*80));
         movedata(FP_SEG(buf1),FP_OFF(buf1),0xb000,offset,2);
     }
/* ------------------------- */
/* --- FUNCTION s_poke() --- */
/* -- < for mono filed > --  */
/* ------------------------- */
void s_poke( unsigned int p, int x, int y,int attrib)
     {
         int offset;
         int *buf1,buf[1];
         int width;
         buf1=buf;
         *buf1=(attrib|p);
         offset=(2 * ((y-1)+(x-1)*80));
         movedata(FP_SEG(buf1),FP_OFF(buf1),0xb000,offset,2);
     }
/* ---------------------------- */
/* --- FUNCTION w_gets() ------ */
/* - < for window get string >- */
/* ---------------------------- */
int w_gets(char *str,int len)
{

    int c,i,rowpt,colpt,curstr,curend,fldend=0;
    char *str1,*strtemp;
    struct rccoord where;
    where=_gettextposition();
    str1=str;strtemp=str;
    curstr=where.col;
    curend=where.col+len-1;
    rowpt=where.row;
    colpt=where.col;
    for(i=0;i<=len-1;i++)
       {
         *strtemp=' ';
         w_poke(' ',rowpt,colpt,0x7000);
         colpt++;strtemp++;
       }
    colpt=curstr;
    CUP(rowpt,colpt);
    while(1)
    {
      while (_bios_keybrd(_KEYBRD_READY)==0);
      c=_bios_keybrd(_KEYBRD_READ);
      switch (c>>8)
       {
        case  1:return(0);                   /* escape    */
        case 14:if (colpt<=curstr)           /* Backspace */
                   break;
                if ((colpt==curend) && (fldend==1))
                   {
                      str--;*str=' ';
                      w_poke(' ',rowpt,colpt,0x7000);
                      CUP(rowpt,colpt);
                      fldend=0;
                      break;
                    }
                colpt--;str--;*str=' ';
                w_poke(' ',rowpt,colpt,0x7000);
                CUP(rowpt,colpt);
                break;

        case 15:break;                       /* Tab       */
        case 57:break;                       /* Spacebar  */
        case 59:                             /* F1        */
        case 60:                             /* F2        */
        case 61:                             /* F3        */
        case 62:                             /* F4        */
        case 63:                             /* F5        */
        case 64:                             /* F6        */
        case 65:                             /* F7        */
        case 66:                             /* F8        */
        case 67:                             /* F9        */
        case 68:                             /* F10       */
        case 71:break;                       /* Home      */
        case 72:break;                       /* Up        */
        case 73:break;                       /* PgUp      */
        case 74:break;                       /* Minus     */
        case 75:if (colpt<=curstr)           /* Left      */
                   break;
                if ((colpt==curend) && (fldend==1))
                   {
                      str--;
                      fldend=0;
                    }
                colpt--;str--;
                CUP(rowpt,colpt);
                break;
        case 76:break;                       /* Keypad    */
        case 77:if(colpt>=curend)            /* Right     */
                  break;
                colpt++;CUP(rowpt,colpt);
                str++;break;
        case 79:break;                       /* End       */
        case 80:break;                       /* Down      */
        case 81:break;                       /* PgDn      */
        case 82:break;                       /* Ins       */
        case 83:break;                       /* Del       */
        case 28:*strtemp='\0';               /* Enter     */
                colpt=curstr;
                for(i=0;i<=len-1;i++)
                   {
                      w_poke(*str1,rowpt,colpt,0x0700);
                      colpt++;
                      str1++;
                    }
                return(1);
        default:
                if ((colpt>=curend) && (fldend==1))
                    break;
                *str=c&0xff;str++;
                w_poke(c&0xff,rowpt,colpt,0x7000);
                if (colpt==curend)
                   {
                      CUP(rowpt,colpt);
                      fldend=1;
                      break;
                    }
                colpt++;CUP(rowpt,colpt);
                break;
      }
    }

}
/* ---------------------------- */
/* --- FUNCTION s_gets() ------ */
/* - < for mono get string > -- */
/* ---------------------------- */
int s_gets(char *str,int len)
{

    int c,i,rowpt,colpt,curstr,curend,fldend=0;
    char *str1,*strtemp;
    struct rccoord where;
    where=_gettextposition();
    str1=str;strtemp=str;
    curstr=where.col;
    curend=where.col+len-1;
    rowpt=where.row;
    colpt=where.col;
    for(i=0;i<=len-1;i++)
       {
         *strtemp=' ';
         s_poke(' ',rowpt,colpt,0x7000);
         colpt++;strtemp++;
       }
    colpt=curstr;
    CUP(rowpt,colpt);
    while(1)
    {
      while (_bios_keybrd(_KEYBRD_READY)==0);
      c=_bios_keybrd(_KEYBRD_READ);
      switch (c>>8)
       {
        case  1:return(0);                   /* escape    */
        case 14:if (colpt<=curstr)           /* Backspace */
                   break;
                if ((colpt==curend) && (fldend==1))
                   {
                      str--;*str=' ';
                      s_poke(' ',rowpt,colpt,0x7000);
                      CUP(rowpt,colpt);
                      fldend=0;
                      break;
                    }
                colpt--;str--;*str=' ';
                s_poke(' ',rowpt,colpt,0x7000);
                CUP(rowpt,colpt);
                break;

        case 15:break;                       /* Tab       */
        case 57:break;                       /* Spacebar  */
        case 59:                             /* F1        */
        case 60:                             /* F2        */
        case 61:                             /* F3        */
        case 62:                             /* F4        */
        case 63:                             /* F5        */
        case 64:                             /* F6        */
        case 65:                             /* F7        */
        case 66:                             /* F8        */
        case 67:                             /* F9        */
        case 68:                             /* F10       */
        case 71:break;                       /* Home      */
        case 72:break;                       /* Up        */
        case 73:break;                       /* PgUp      */
        case 74:break;                       /* Minus     */
        case 75:if (colpt<=curstr)           /* Left      */
                   break;
                if ((colpt==curend) && (fldend==1))
                   {
                      str--;
                      fldend=0;
                    }
                colpt--;str--;
                CUP(rowpt,colpt);
                break;
        case 76:break;                       /* Keypad    */
        case 77:if(colpt>=curend)            /* Right     */
                  break;
                colpt++;CUP(rowpt,colpt);
                str++;break;
        case 79:break;                       /* End       */
        case 80:break;                       /* Down      */
        case 81:break;                       /* PgDn      */
        case 82:break;                       /* Ins       */
        case 83:break;                       /* Del       */
        case 28:*strtemp='\0';               /* Enter     */
                colpt=curstr;
                for(i=0;i<=len-1;i++)
                   {
                      s_poke(*str1,rowpt,colpt,0x0700);
                      colpt++;
                      str1++;
                    }
                return(1);
        default:
                if ((colpt>=curend) && (fldend==1))
                    break;
                *str=c&0xff;str++;
                s_poke(c&0xff,rowpt,colpt,0x7000);
                if (colpt==curend)
                   {
                      CUP(rowpt,colpt);
                      fldend=1;
                      break;
                    }
                colpt++;CUP(rowpt,colpt);
                break;
      }
    }

}
