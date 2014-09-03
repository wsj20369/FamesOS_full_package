

#include "dos.h"
#include "stdio.h"
#include "stdlib.h"
#include "data.str"
extern STRU *finder;
extern STRU *header;
extern FILE *headno;
extern int flag;

FILE *f_read(char *filename)
{
  FILE *filehead;
  int chksum;
  chksum=access(filename,00);
  if (chksum==0)
     filehead=fopen(filename,"r+t");
  else
     {
       if ((filehead=fopen(filename,"a+t"))==0)
          printf("file open error");
      }
  f_load(filehead);
  return(filehead);
}

/* ---------------------------- */
/* ---- FUNCTION f_load() ----- */
/* ---------------------------- */
f_load(FILE *head)
{
     STRU *booker;
     int fstatus;
     while(1)
       {
            booker=(STRU *) malloc(sizeof(STRU));
            fstatus=fscanf(head,"%11s",booker->bokname);
              if ((fstatus==EOF)|(fstatus==0))
                  {
                     rewind(head);
                     return;
                  }
            fscanf(head,"%11s",booker->bokauther);
            fscanf(head,"%5s",booker->bokstore);
              if(flag==1)
                {
                     header=booker;
                     booker->next=booker;
                     booker->prev=booker;
                     finder=booker;
                     flag=2;
                }
              else
                {
                     booker->prev=finder;
                     finder->next=booker;
                     finder=booker;
                     finder->next=header;
                }

      }
 }

/* ---------------------------- */
/* ---- FUNCTION f_save() ----- */
/* ---------------------------- */
f_save(FILE *fllbl,STRU *llist)
{
      do
        {
            fprintf(fllbl,"%-11s",llist->bokname);
            fprintf(fllbl,"%-11s",llist->bokauther);
            fprintf(fllbl,"%-5s",llist->bokstore);
            llist=llist->next;
         } while (llist!=header);
}
