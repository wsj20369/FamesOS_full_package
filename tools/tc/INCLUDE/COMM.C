
/*
  ┌──────────────────────────┐
  │  書名 :   TURBO C 通訊程式設計 ----技巧與實務      │
  │  作者 :   楊玄周 楊玄彰                            │
  │  出版 :   波全資訊股份有限公司                     │
  └──────────────────────────┘
*/

/*      COMM.C  */

#include        <stdio.h>
#include        <stdlib.h>
#include        <stdarg.h>
#include        <dos.h>
#include        "utility.h"
#include        "comm.h"


/*
   PIC( Programmable Interrupt Controller) 8259 I/O address

   I/O port : ( for PC )
        0x20 = used to send the end of interrupt to the 8259
        0x21 = used to masking interrupts

   Interrupts handled by PC
        IRQ0 = Timer
        IRQ1 = Keyboard
        IRQ2 = Reserved
        IRQ3 = COM2-COM8
        IRQ4 = COM1
        IRQ5 = Hard Disk
        IRQ6 = Floppy Disk
        IRQ7 = Printer
*/
#define PIC8259Mask   0x21
#define PIC8259EOI    0x20


/* used to store original ISR address for INT 0Bh & INT 0Ch */
void interrupt (*OldIntB)();
void interrupt (*OldIntC)();


/*
   base I/O address for individual communication port
   NOTES:
        in PC bus, only COM1 & COM2 are available
        in Micro Channel, we can have up to eight port

   Therefore, COM3-COM8 are only available for most IBM PS/2
   Unfortunately, most PC in Taiwan are not Micro channel bus, so be careful
        not to use COM3-COM8
*/
static int  PortBase[8] =
            {
                0x3F8,  0x2F8,  /* COM1, COM2 */
                0x3220, 0x3228, /* COM3, COM4 */
                0x4220, 0x4228, /* COM5, COM6 */
                0x5220, 0x5228  /* COM7, COM8 */
            };


/* an array to store those already open/intialized communication  */
static COMM *PortStru[8];


/* BIT definition */
#define B0      0x01    /* bit 0 */
#define B1      0x02    /* bit 1 */
#define B2      0x04    /* bit 2 */
#define B3      0x08    /* bit 3 */
#define B4      0x10    /* bit 4 */
#define B5      0x20    /* bit 5 */
#define B6      0x40    /* bit 6 */
#define B7      0x80    /* bit 7 */


/*

   Set DTR on

   NOTES :
   1. DTR --- Data Terminal Ready
   2. DTR line tells the modem that the computer is powered on and ready to
        receive data from the modem.
   3. DTR is located at MCR bit 0
*/

void  comm_setDTR( COMM *Port )
{
BYTE    value;

        /* get original value of MCR */
        value = inportb( Port->base+MCR );
        /* set bit 0 on, feed back to MCR */
        outportb( Port->base+MCR, value|B0 );
}


/*
   Reset DTR off
*/
void  comm_resetDTR( COMM *Port )
{
BYTE    value;

        /* get original value of MCR */
        value = inportb( Port->base+MCR );
        /* reset bit 0 off, feed back to MCR */
        outportb( Port->base+MCR, value&(~B0) );
}


/*
   Set Break on
   NOTES :
   1. Break is located at LCR bit 6

 */
void  comm_setBreak( COMM *Port )
{
BYTE    value;

        /* get original value of LCR */
        value = inportb( Port->base+LCR );
        /* set bit 6 on, feed back to LCR */
        outportb( Port->base+LCR, value|B6 );
}


/*
   Reset Break off
*/

void  comm_resetBreak( COMM *Port )
{
BYTE    value;

        /* get original value of LCR */
        value = inportb( Port->base+LCR );
        /* reset bit 0 off, feed back to LCR */
        outportb( Port->base+LCR, value&(~B6) );
}


/*

   Query the status of DTR line
   return value : TRUE,  if DTR on
                  FALSE, if DTR off

 */
BOOL  comm_isDTR( COMM *Port )
{
        if ( inportb(Port->base+MCR)&B0 )
                return TRUE;

        return FALSE;
}


/*
   Query the status of Break line
   return value : TRUE,  if Break on
                  FALSE, if Break off
 */
BOOL  comm_isBreak( COMM *Port )
{
        if ( inportb(Port->base+LCR)&B6 )
                return TRUE;

        return FALSE;
}


/*
   Query the status of DCD line
   return value : TRUE,  if DTR on
                  FALSE, if DTR off
   NOTES :
   1. DCD --- Data Carrier Detector
   2. DCD line tells that the modem is connected to another modem.
   3. DCD is located at MSR bit 7
 */

BOOL  comm_isDCD( COMM *Port )
{
        if ( inportb(Port->base+MSR)&B7 )
                return TRUE;

        return FALSE;
}


/*
   Query the status of RI line
   return value : TRUE,  if DTR on
                  FALSE, if DTR off

   NOTES :
   1. RI --- Ring Indicator
   2. RI line tells that the telephone is ringing.
   3. RI is located at MSR bit 6
 */

BOOL  comm_isRing( COMM *Port )
{
        if ( inportb(Port->base+MSR)&B6 )
                return TRUE;

        return FALSE;
}


/*
   Setting the baud rate
   return value :
        -1 : Port not available
         0 : OK

   NOTES:
   1. When we want to set baud rate, we have keep bit 7 of LCR ON.
   2. Then assign low byte of baud rate divisor to BAUDL, and high byte
        to BAUDH.

 */
int comm_setBaud( COMM *Port, int baud )
{
register int RegLCR; /* will hold the Line Control Register contents */

        if ( !Port )
            return -1;

        /* get original value of LCR */
        RegLCR = inportb( Port->base+LCR );

        /* set up to set buad rate */
        /* set bit 7 of LCR on */
        outportb( Port->base+LCR, RegLCR|B7 );

        /* compute baud rate divisor */
        baud = (int)( 115200L/(long)baud );

        /* setting baud rate, there two way to do
           1. easy way */
        outport( Port->base+BAUDL, baud );

        /* 2. hard way --- assign high & low byte separately
              High byte
          outportb( Port->base+BAUDL,baud & 0xff );
              Low  byte
          outportb( Port->base+BAUDH,baud >> 8 );    */

        /* reset original value of LCR */
        outportb( Port->base+LCR, RegLCR );

        return 0;
}


/*
   Change the communications parameters of Port that has already been opened.
   return value :
        -1 : Port not available
         0 : OK

   Layout of LCR(Line Control Register)
        BIT 0-1 : data bit
                7 bits --- 10
                8 bits --- 11
        BIT 2   : stop bit
                1 bit  --- 0
                2 bit  --- 1
        BIT 3-5 : parity
                NO     --- 000          // ignore
                ODD    --- 001
                EVEN   --- 011
                MARK   --- 101          // always ON
                SPACE  --- 111          // always OFF

   Please refer to program COMM.H

   NOTES :
   1. The other function parameters are the same as the corresponding
        parameters of the comm_open function.

 */
int comm_params( COMM *Port, int baud, int parity, int dataBit, int stopBit )
{
register int RegLCR;          /* will hold the Line Control Register contents */

        if ( !Port )
            return -1;

        /* set up to set buad rate */
        if ( comm_setBaud( Port, baud ) )
                return -1;

        /* set data, parityity, and stop bits */
        RegLCR= (dataBit) | (stopBit) | (parity);
        outportb( Port->base+LCR, RegLCR );

        return 0;
}


/*
   Return the number of the COM port with which Port is associated.
   return value :
        0   : not associated with any port.
        1-8 : COM1-COM8
*/
int comm_portNum( COMM *Port )
{
register int i;

     if ( !Port )
        return( 0 );

     for ( i=0; i<8 ; i++ )
     {
         if ( PortStru[i]==Port )
             return( i+1 );
     }

     return 0;
}


/*
   Get the content of the register specified as UARTRegister
   return value :
        -1     : not available
        others : content
*/

int comm_getStatus( COMM *Port, int UARTRegister )
{
    if ( !Port )
        return -1;

    switch ( UARTRegister )
    {
            case LCR :
                 return( inportb( Port->base+LCR ) );
            case LSR :
                 return( inportb( Port->base+LSR ) );
            case MCR :  /* bit 5-7 not used. Therefore, we mark it off. */
                 return( inportb( Port->base+MCR ) & 0X1F );
            case MSR :
                 return( inportb( Port->base+MSR ) );
    }

    return -1;
}

/*
   Set the content of the register specified as UARTRegister.
   Only available for LCR & MCR, since LSR & MSR not suitable for changing
        their contents.

 */
void comm_setStatus( COMM *Port, int UARTregister , int newStatus )
{
    if ( !Port )
        return;

    switch ( UARTregister )
    {
           case LCR :
                outportb( Port->base+LCR, newStatus );
           case MCR :
                outportb( Port->base+MCR, newStatus );
    }
}


/*
   Architeture of Input Buffer
   ===========================

        0000000000000000XXXXXXXXXXXXXXXX0000000000000000
        |               |               |               |
        |               |               |               |
        inQue           inQueLast       inQueFirst      inQueStop
        ========        ============    ============    =========
        begin of        where to get    where to put    end of
        buffer          by proram       by TSR          buffer

   Architeture of Output Buffer
   ============================

        0000000000000000XXXXXXXXXXXXXXXX0000000000000000
        |               |               |               |
        |               |               |               |
        outQue          outQueLast      outQueFirst     outQueStop
        ========        ============    ============    =========
        begin of        where to get    where to put    end of
        buffer          by ISR          by program      buffer

        NOTES:
        1. QueLast  catch up QueFirst ===> overrun
        2. QueFirst catch up QueLast  ===> overflow
        3. QueLast & QueFirst reach QueStop, we should wrap it back.
   */



/*
   interrupt handler for COM2-COM8.
   NOTES:
   1. 'interrupt' is a special key word for Turbo C, which is not portable to
        other machine.
   2. Since we implement the ISR in high level language 'C', it will probably
        be a little bit slow, but it will sufficient for most case.
   3. Anyway, if you want to speed up this ISR, we will recommend to you to
        rewrite it in Assembly.
   4. We have mentioned that only Micro Channel Bus configuration can support
        COM3-COM8.
   5. In Micro Channel Bus configuration, COM2-COM8 are all share the Interrupt
        0x0B

   Layout for IIR
        BIT 0   :
                More than more interrupt has occurred
        BIT 1-2 :
                00 = Change in modem status register
                01 = Transmitter holding register(THR) empty
                10 = Data received
                11 = Data reception error or break
   NOTES:
        Whenever an interrupt occurred, IIR register can tell us what cause it.
 */
void interrupt NewIntB( void )
{
COMM        *Port;
BYTE        *BufPoint;
register int i,RegIIR;

     /* COM2 - COM8 */
     /* scan from COM2 to COM8 */
     disable();
     for( i=1; i<8; i++ )
     {
         Port = PortStru[i];
         if ( Port ) /* if this port had been opened. */
         {
             RegIIR = inportb( Port->base+IIR );

             /* Previous byte was received by other end */

             if ( RegIIR == 4 )
             {
                 /* point to the next ready byte */
                 BufPoint = Port->inQueFirst;

                 /* read the byte from the UART */
                 /* put into input buffer --- inQueFirst */
                 *BufPoint = inportb(Port->base+DATA);
                 BufPoint++;
                 /* increase the count of bytes in the buffer */
                 Port->inNum++;

                 /* if BufPoint reach up end of buffer, wrap it. */
                 if ( BufPoint == Port->inQueStop )
                     BufPoint = Port->inQue;

                 /* handle First-Last collision */
                 if ( BufPoint == Port->inQueLast )
                 {
                     /* overrun handling, sacrify one byte */
                     Port->inQueLast++;
                     Port->inNum--;

                     /* if reach end of buffer, wrap it. */
                     if ( Port->inQueLast == Port->inQueStop )
                         Port->inQueLast = Port->inQue;
                 }
                 Port->inQueFirst = BufPoint;      /* update bufFirst */
             }


             /* if Tx register empty, send out one byte */

             if ( RegIIR==2 && Port->outNum )
             {   /* starting to send */
                 /* point to next 'ready for send' character. */
                 BufPoint = Port->outQueLast;
                 outportb( Port->base+DATA, *BufPoint++ );
                 Port->outNum--;

                 /* if reach end of buffer, wrap it. */
                 if ( BufPoint == Port->outQueStop )
                     BufPoint = Port->outQue;

                 Port->outQueLast = BufPoint;
             }
         }
     }

     /* telling PIC 8259 that it's end of interrupt */
     outportb( PIC8259EOI, 0x20 );

     enable();
}


/*
   interrupt handler for COM1
 */
void interrupt NewIntC( void )
{
COMM        *Port;
BYTE        *BufPoint;
register int RegIIR;

     /* COM1 */
     enable();
     Port=PortStru[0];

     while ( Port )
     {
         RegIIR = inportb( Port->base+IIR );

         if ( RegIIR & 0x01 )
         {
             /* telling PIC 8259 that it's end of interrupt */
             outportb( PIC8259EOI, 0x20 );
             return;
         }

         if ( RegIIR == 0 )
         {
                Port->RegMSR = inportb( Port->base+MSR );
                continue;
         }

         if ( RegIIR == 6 )
         {
                Port->RegLSR = inportb( Port->base+LSR );
                continue;
         }


         /* if Tx register empty, send out one byte */

         if ( RegIIR==2 && Port->outNum )
         {
             if ( Port->TxDelay )
                delay( Port->TxDelay );

             /* fetch next ready to send byte */
             BufPoint = Port->outQueLast;
             /* send it */
             outportb( Port->base+DATA, *BufPoint++ );

             /* if reach end of buffer, wrap it */
             if ( BufPoint == Port->outQueStop )
                  BufPoint = Port->outQue;

             /* update outQueLast */
             Port->outQueLast = BufPoint;
             Port->outNum--;

             continue;
         }

         /* Previous byte was received by other end */

         if ( RegIIR == 4 )
         {
             /* point to next available byte in the buffer */
             BufPoint = Port->inQueFirst;

             /* read the byte from the UART */
             *BufPoint++ = inportb( Port->base+DATA );
             /* update count of bytes in the buffer */
             Port->inNum++;

             /* wrap if necessary */
             if ( BufPoint == Port->inQueStop )
                  BufPoint = Port->inQue;

             /* handle First-Last collision */
             if ( BufPoint == Port->inQueLast )
             {
                 /* overrun --- sacrify one byte */
                 Port->inQueLast++;
                 Port->inNum--;

                 /* if reach end of buffer, wrap it. */
                 if ( Port->inQueLast == Port->inQueStop )
                      Port->inQueLast = Port->inQue;
             }

             /* update inQueFirst */
             Port->inQueFirst=BufPoint;
         }
     }
}


/*
   Open an async port with the given characteristics.

   return value :
        NULL   : port can not be open successfully
        others : return pointer to communication structure COMM.

   NOTES:
   1. Set up the protocol, including port, baud rate, parity, data bit,
        stop bit.
   2. Allocate memory space for input/output buffer.
   3. Protocol parameters are same as functio comm_paras(...)
   4. Be aware that parameters are not validated, so be careful the value pass
        to the function.
   5. The inQuesize and outQuesize parameters specify the sizes of the input/
        output buffer.
   6. Input buffer is compulsory. Depending on application, the demanding size
        can be different.
   7. Output buffer is optional. It can be zero.

   Algorithm :
   1. Check whether this port had been opened or not? if yes, close it.
   2. Allocate memory to store struct COMM.
   3. Allocate memory for input buffer.
   4. Allocate memory for output buffer.
   5. Memorize old ISR vector address.
   6. Hook up new ISR.
   7. Set up the communication parameter, such as baud rate, parity...
   8. Enable interrupt by change the contents of PIC 8259.
   9. Setting IER register of UART 8250 to specify interrupt type.
   10. Setting MCR register of UART 8250 to enable interrupt and set DTR & RTS
 */

COMM *comm_open( int port, int baud, int parity, int dataBit,
                 int stopBit, int inQueSize, int outQueSize)
{
int IRQMask;

        /* validate port that is legal or not */
        if ( port>8 || port<1 )
            return NULL;
        port--;

        /* check the port had been opened or not. */
        if ( PortStru[port] )
        {
            /* if this port is already open, close it */
            /* free every memory has been allocated by it */
            /* and lately re-open a new one */
            free( PortStru[port]->inQue );      /* free input buffer */
            if ( PortStru[port]->outQue )       /* free output buffer */
                free( PortStru[port]->outQue ); /*  if necessary */
            free( PortStru[port] );             /* free structure COMM itself */
            PortStru[port] = NULL;
        }

        /* Memory allocation for input/output buffer and structure COMM */

        /* allocate a new space for structure COMM */
        PortStru[port] = (COMM *) malloc( sizeof(COMM) );
        if ( PortStru[port] == NULL )           /* if memory allocation failed. */
            return NULL;

        /* allocate space for the input buffer */
        PortStru[port]->inQue = (char *) malloc( inQueSize );
        if ( PortStru[port]->inQue == NULL )    /* if memory allocation failed */
        {
            free( PortStru[port] );
            return NULL;
        }

        /* allocate space for output buffer, if necessary. */
        if ( outQueSize )
        {
            /* make space for the output buffer */
            PortStru[port]->outQue = (char *) malloc( outQueSize );             if ( PortStru[port]->outQue == NULL )
            {   /* memory allocation failed */
                free( PortStru[port]->inQue );  /* free input buffer allocated */
                free( PortStru[port] );         /* free structure COMM */
                return NULL;
            }
        }
        else
            PortStru[port]->outQue = NULL;

        /* assign proper value into structure COMM */

        PortStru[port]->base        = PortBase[port];
        PortStru[port]->inQueStop   = PortStru[port]->inQue+inQueSize;
        PortStru[port]->inQueFirst  = PortStru[port]->inQue;
        PortStru[port]->inQueLast   = PortStru[port]->inQue;
        PortStru[port]->inNum       = 0;
        PortStru[port]->outQueStop  = PortStru[port]->outQue+outQueSize;
        PortStru[port]->outQueFirst = PortStru[port]->outQue;
        PortStru[port]->outQueLast  = PortStru[port]->outQue;
        PortStru[port]->outNum      = 0;

        /* OK! Finally, allocation for buffer is done! */
        /* Now! we have to go on to hook up interrupt and enable it. */


        disable();

        /* memorize old ISR vector
           hook up the new ISR
                INT 0x0B for COM2-COM8
                INT 0x0C for COM1
        */
        if ( port )
        {
            /* make sure that int 0Bh is hooked */
            /* COM2-COM8 */
            if ( OldIntB == NULL )
            {   /* for INT 0x0B */
                /* OldIntB is used to store old address for ISR of INT 0x0B */
                /* NewIntB() will our new ISR */
                OldIntB = getvect( 0x0B ); /* store the original vector */
                setvect( 0x0B, NewIntB );  /* install new ISR */
            }
        }
        else
        {
            /* make sure that int 0Ch is hooked */
            /* COM1 only */
            if ( OldIntC == NULL )
            {   /* for INT 0x0C */
                /* OldIntC is used to store old address for ISR of INT 0x0C */
                /* NewIntC() will our new ISR */
                OldIntC = getvect( 0x0C );  /* store the original vector */
                setvect( 0x0C, NewIntC );   /* install new ISR */
            }
        }


        /* set up the port itself
                including baud rate, parity, data bit and stop bit   */

        comm_params( PortStru[port], baud, parity, dataBit, stopBit );

        /* adjust the IRQ mask for PIC 82559
                IRQ3 for COM2-COM8
                IRQ4 for COM1 */

        IRQMask=inportb( PIC8259Mask );      /* get the current IRQ mask */
        if ( port )
            /*  COM2 - COM8 */
            IRQMask &= 0xf7;                 /* enable IRQ 3 */
        else
            /* COM1 */
            IRQMask &= 0xef;                 /* enable IRQ 4 */

        /* set up PIC 8259 mask */
        outportb( PIC8259Mask, IRQMask );    /* set the new IRQ mask */

        outportb( PIC8259EOI,  0x64 );



        /* set up UART 8250, and ready to accept interrupt */

        /* Layout of IER( Interrupt Enable Register )
                BIT 0   = Data Received
                BIT 1   = THR empty
                BIT 2   = Data error or break
                BIT 3   = MSR change
                BIT 4-7 = Unused
        */
        if ( outQueSize )
            /*  enable DATA_READY and XMIT_BUF_MT */
            outportb( PortStru[port]->base+IER, 0x0F );
        else
            /* enable DATA_READY only */
            outportb( PortStru[port]->base+IER, 0x0D );

        /* Layout of MCR( Modem Control Register )
                BIT 0   = Set DTR line active
                BIT 1   = Set RTS line active
                BIT 2   = Hayes Reset
                BIT 3   = Enable Interrupt
                BIT 4-7 = Unused  */

        /* enable interrupts, DTR, and RTS */
        outportb( PortStru[port]->base+MCR, 0x0b );

        PortStru[port]->RegLSR = inportb( PortStru[port]->base+LSR );
        PortStru[port]->RegMSR = inportb( PortStru[port]->base+MSR );

        enable();

        /* return pointer to communication structure COMM. */

        return PortStru[port];

}




/*
   Close the async port with which Port is associated.

   no return value

   NOTES:
   1. Free memory allocated for input/output buffer.
   2. Free memory allocated for the control structure itself.
   3. The interrupts that were enabled when the port was opened are
        disabled.

   Algorithm:
   1. Check if the port had been opened. If no, simply return.
   2. Reset MCR & IER of UART 8250 to disable interrupt.
   3. Reset PIC 8259 to disable interrupt.
   4. Free memory allocated for input/output buffer.
   5. Free memory allocated for structure COMM.

   For example:

      COMM *Port;
      .
      .
      Port=comm_open(2,2400,PARITY_NONE,BIT8,STOP1,4096,1024);
      .
      .
      comm_close(Port);
*/

void  comm_close( COMM *Port )
{
register int IRQMask, PortNo;

          if ( !Port )
             return;

          /* find out had been opened or not. if not return. */

          for ( PortNo=0; PortNo<8; PortNo++ ) /* find this port in the array */
          {
              if ( PortStru[PortNo] == Port )   /* OK! we got it */
                 break;
          }
          if ( PortNo > 7 )
                 return;

          disable();

          /* reset MCR & IER to disable interrupt */

          outportb( Port->base+MCR, 0 );
          outportb( Port->base+IER, 0 );

          /* unhook from the interrupt vector table if this is */
          /* is the last port open that uses this vector. */

          PortStru[PortNo] = NULL;              /* remove this port */
          if ( PortNo == 0 )                    /* if COM1 */
          {
              /* mark out IRQ4 from 8259 */
              IRQMask = inportb( PIC8259Mask ); /* get the current IRQ mask */
              IRQMask |= 0x10;                  /* disable IRQ 4 */
              outportb( PIC8259Mask,IRQMask );  /* set the new IRQ mask */

              /* restore old ISR */
              setvect( 0x0C, OldIntC );         /* restore old ISR for 0x0C */
              OldIntC = NULL;                   /* tells never install new ISR */
          }
          else
          {
              /* for COM2-COM8 */
              for( PortNo=1; PortNo<8; PortNo++)
              {
                  if  ( PortStru[PortNo] != NULL )
                      break;
              }

              /* Since COM2-COM8 share this interrupt */
              /* if somebody is still using it, we can't disable it. */
              if ( PortNo==8 )  /* no others ports are using this interrupt */
              {
                  /* mark out IRQ3 from 8259 */
                  IRQMask = inportb( PIC8259Mask);/* get current IRQ mask */
                  IRQMask |= 0x08;               /* disable IRQ 3 */
                  outportb( PIC8259Mask,IRQMask);/* set the new IRQ mask */

                  /* restore old ISR */
                  setvect( 0x0B, OldIntB );      /* restore old ISR for 0x0B */
                  OldIntB=NULL;                  /* tells never install new ISR */
              }
          }

          enable();

          /* deallocate the memory used by this port */
          if ( Port->outQue != NULL )
              free( Port->outQue );  /* free memory for output buffer */
          free( Port->inQue );       /* free memory for input buffer */
          free( Port );              /* free memory for structure COMM */

          return;
}


/*
   Return how many character in input buffer
 */

unsigned comm_inNUM( register COMM *Port )
{
        return( Port->inNum );
}


/*
   Return how many character in output buffer
 */

unsigned comm_outNUM( register COMM *Port )
{
        return( Port->outNum );
}




/*
   Send the character 'ch' to the 'Port'.

   return value :
        -1 : Failed
                1). Port not opened
                2). We already receive an XOFF from other end, which
                        inhibit us to send any character to them
                3). Overflow occurred.
                        Ouput buffer overflow.
        ch : the character to be sent, mean success

   NOTES:
   1. If there is no output buffer, wait until Port to be ready to
        accept a character, and then send the character to Port.
   2. If there is an output buffer, what we should do will depend on cases

   Algorithm:

        if (Port is not opend)
                return -1;

        if (Port already received XOFF)
                return -1;

        if (Port has no output buffer )
        {
                wait until port_ready_Tx
                send the characeter to THR of UART
        }

        if (output buffer empty)
        {
            if (port_ready_Tx)
                transmit_the_character
            else
                send the characeter to THR of UART
        }
        else
        {
            send the characeter to THR of UART
            if (output buffer overflow)
                return -1
            else
                return (character)
        }
 */

char comm_putc( register COMM *Port, char ch )
{
BYTE *BufferPoint;

    /* 1) Port not opened
       2) We already got an XOFF from other end, which block us from sending
                out any character out
    */
    if ( !Port || Port->recvXoff!=0 )
       return -1;

    if ( Port->outQue )
    {
        /* if we have output buffer */

        /* no other characters waiting for send, and UART THR is empty
           LSR(Line Status Register) BIT 4 --- THR is empty
                Ready to output a character to the line
         */
        if ( Port->outNum==0 && (inportb(Port->base+LSR) & 0x20) )
        {
            /* port is ready now, send right now */
            outportb( Port->base+DATA, (unsigned char)ch );
        }
        else /* this character must be put into the output buffer */
        {
            /* Move to address where we should put the character to */
            BufferPoint = Port->outQueFirst;
            /* Put into buffer */
            *BufferPoint++ = (BYTE)ch;

            /* if reach to end of buffer, wrap it */
            if ( BufferPoint == Port->outQueStop )
                BufferPoint = Port->outQue;

            /* if overflow occurred, return FAILED */
            if ( BufferPoint == Port->outQueLast )
                return -1;

            /* update the data */
            Port->outQueFirst = BufferPoint;
            Port->outNum++;
        }
    }
    else
    {
        /* Since we don't have output buffer, */
        /* we got to wait till 8250 is ready to send */

        while( (inportb(Port->base+LSR) & 0x20) == 0 );
        outportb( Port->base+DATA, (unsigned char)ch );
    }

    /* Success */
    return ch;
}


/*
   Send a string to the Port.

   return value:
        -1     : Error
        others : the value of the last character that was sent.
                 If the string is empty, return a value of zero.

   NOTES:
   1. The string must be ASCIIZ, which means string terminated by null.
   2. This function does NOT append '\n' or '\r' character to the string.
 */

int comm_puts( register COMM *Port,register char *string  )
{
       /* Port not opened, return FAILED */
       if ( !Port )
            return -1;

       /* If is a null string, return 0 */
       if ( !*string )
            return 0;

       /* output one byte by one byte */
       while( *string )
       {
            if ( comm_putc( Port,*string ) == *string )
            {
                /* if return character is same as the one we send, then sucess */
                /* go on to send next */
                /* if not success, we won't go on to the next character */
                string++;
             }
       }

       /* if sucess, then send the last character of the string */
       return(*(string-1));
}


/*
   Get character input buffer associated with Port.

   return value :
        -1    : failed.
        other : the character we got.
*/

char comm_getc( register COMM *Port )
{
char ch, *BufferPoint;

        if ( !Port )
           return -1;

        /* point to the next byte in the buffer */
        BufferPoint=Port->inQueLast;

        /* if there is nothing in the buffer, return -1 */
        if ( BufferPoint == Port->inQueFirst )
            return -1;

        /* update data */
        ch = *BufferPoint++;
        Port->inNum--;

        /* if reach end of buffer, wrap it */
        if ( BufferPoint == Port->inQueStop )
            BufferPoint = Port->inQue;

        Port->inQueLast = BufferPoint;

        /* return the value we got */
        return ch;
}


/*
   Wait & Get character input buffer associated with Port.

   return value :
        FALSE : fail
        OK    : the value in ch
*/

BOOL comm_inkey( register COMM *Port, char *ch )
{
char *BufferPoint;

        if ( !Port )
           return FALSE;

        /* point to the next byte in the buffer */
        BufferPoint=Port->inQueLast;

        /* if there is nothing in the buffer, return -1 */
        while ( BufferPoint == Port->inQueFirst );

        /* update data */
        *ch = *BufferPoint++;
        Port->inNum--;

        /* if reach end of buffer, wrap it */
        if ( BufferPoint == Port->inQueStop )
            BufferPoint = Port->inQue;

        Port->inQueLast = BufferPoint;

        /* OK! we got the value */
        return TRUE;
}


/*
   Get a string from the input buffer associated with Port.

   return value:
        NULL  : failed
        other : the string we got

   NOTES:
   1. Read up to MaxLen-1 characters from the port or until receive '\r'
        Assign zero to end of string to construct ASCIIZ, and return the string.
   2. Spend MaxTime+1 eighteenths of a second to get the string.
   3. If more than one character is successfully received, return the string.
   4. If no characters have been read at MaxTime+1 eighteenths of a second,
        return NULL.
   5. This function will ignore every '\n' character.
 */

char *comm_gets( COMM *Port, char *string, int MaxLen,  int MaxTime )
{
WORD               count;
char              *oldString;

         /* if open not opened */
         if ( !Port )
             return NULL;

         /* setup timer to count down */
         timerSet( MaxTime );

         count=1;               /* counting the number of character we got */
         oldString=string;      /* store old address of string */

         /* if time is not up, and not got enough character */
         while( timerIsNotUp() && count<MaxLen )
         {
              /* if not overrun */
              if ( Port->inQueFirst != Port->inQueLast )
              {
                 /* add only non-null characters to the string */
                 if ( (*string=comm_getc(Port)) != -1 )
                 {
                     /* ignore every '\n' */
                     if ( *string == '\n' )
                         continue;

                     /* we receive '\r', we treat it as EOL */
                     if ( *string == '\r' )
                     {
                         break;         /* terminate the fetching */
                     }
                     else
                     {
                         string++;      /* go on to get another character */
                         count++;
                     }
                 }
              }
         }

         /* assign zero to end of string to construct ASCIIZ */
         *string='\0';

         /* if we haven't receive any character */
         if ( oldString == string )
              oldString = NULL;

         timerUnSet();

         /* if we got any character, we will return the string we got */
         /* if not, will return NULL */
         return oldString;
}


/*
   Put the character 'ch' back into the buffer.

   return value :
        -1 : failed.
        ch : the character we want to push --- success

   NOTES:
   1. This operation may be performed until the buffer is full of the character
        that have been pushed into it.
   2. The character will become the next available character to read.
*/

char comm_ungetc( register COMM *Port, char ch  )
{
        /* if port not opened, return -1 */
        if ( !Port )
           return -1;


        /* disable interrupt to avoid collision due to coming in character
                which is going into input buffer */

        disable();

        /* looking for address to put back */

        /* inQueLast is the place we normally fetch data
           Therefore, step back one space it will become the most likely
                address to put back
           And if success, it will also become the next character to fetch */

        Port->inQueLast--;

        /* if pass over begin of buffer, wrap it back */
        if ( Port->inQueLast < Port->inQue )
             Port->inQueLast = Port->inQueStop - 1;

        /* avoid overflow, we won't allow to put back */
        if ( Port->inQueFirst == Port->inQueLast )
        {
            /* restore old inQuelast */
            Port->inQueLast++;

            /* if reach end of buffer, wrap it */
            if ( Port->inQueLast == Port->inQueStop )
                Port->inQueLast = Port->inQue;

            enable();           /* enable */
            return -1;          /* can't put back */
        }

        /* OK! Now, we can put it back */

        *(Port->inQueLast) = (BYTE)ch;

        /* enable interrupt */

        enable();

        return ch;
}

/*
   Get 'Num' objects of size 'Size' from Port within MaxTime 1/18 seconds

   return value :
        -1    : failed
        other : the number of size we got

   NOTES:
   1. The data we got will be put into 'buffer'.
   2. Useful for fetch array of fixed size object, such as structure.
*/

int      comm_read(COMM *Port,char *buffer,int Size,int Num,int MaxTime )
{
int     count;
BYTE    *BufferPoint;

        /* if not opened */
        if ( !Port )
           return -1;

        /* set timer on, and start count down */
        timerSet( MaxTime );
        BufferPoint = (BYTE *)buffer;
        Num *= Size;            /* the maximun length we can fetch */

        /* keep on fetch until time is up or maximun length is reach */
        for( count=0; count<Num && timerIsNotUp(); )
        {
            /* checking overrun status */
            if ( Port->inQueFirst != Port->inQueLast )
            {
                /* if not, get one more character from input buffer */
                *BufferPoint++ = comm_getc( Port );
                count++;
            }

        }

        timerUnSet();
        /* return total number we got */
        return( count/Size );
}


/*
   Send 'Num' objects of size 'Size' toh 'Port' from 'buffer'.

   return value :
        -1    : failed
        other : number of size object we got
*/

int comm_write( COMM *Port, char *buffer, int Size, int Num   )
{
int   count;

        /* if port is opened */
        if ( !Port )
            return -1;

        Num*=Size;              /*total number of character to send */
        count=0;

        while ( count < Num )
        {
            /* send OK! go on next one */
            if ( comm_putc( Port, *buffer ) == *buffer )
            {
                buffer++;
                count++;
            }
        }


        /* number of size object we got */
        return(Num/Size);

}


/*
   Format the variable argument according to 'format' and send to Port.

   return value :
        -1    : failed
        other : length of string we send out

   NOTES:
   1. This is a very good example show us how to implement a variable argument
        list in 'C'.
   2. In this function va_list, va_start(), va_end() is standard ANSI C
        macro definition. More detail information, please refer to your
        C manual.
*/

int comm_printf( register COMM *Port, char *format, ... )
{
register char storage[1024];    /* a large storage */
int           count;
va_list       ArgPointer;       /* initialization of variable argument */

        /* if port not opened */
        if ( !Port )
            return -1;

        /* Macro that begin variable argument */
        va_start( ArgPointer, format );
        vsprintf( storage, format, ArgPointer );

        /* send up to 1024 character, or encounter end of string --- ASCIIZ */
        for( count=0; count<1024 && storage[count]; count++)
        {
            comm_putc( Port, (unsigned char)storage[count] );
        }

        /* Macro that end variable argument access */
        va_end( ArgPointer );

        /* number of character we send out */
        return count;
}


/*
   Wait for 'MaxTime' 1/18 second for a character to come in at 'Port'.

   return value :
        -1 : failed(unopened)
         1 : no character come in
         0 : have some characters come in

   NOTES:
   1. For not opened port, this function will return -1, it will be seem like
        eof status.
   2. Therefore, we assume eof status means no character come in for a period
        of time.
 */

int comm_eof( register COMM *Port, int MaxTime )
{
       /* if not opened */
       if ( !Port )
           return -1;

       /* set timer, start to count down */
       timerSet( MaxTime );

       /* wait right here, will be break for following two condition */
       /* 1) some character come in */
       /* 2) time is up */

       while(   Port->inQueFirst==Port->inQueLast
             && timerIsNotUp() );

       timerUnSet();

       /* if some character come in, not EOF status */
       if ( Port->inQueFirst != Port->inQueLast )
           return 0;

       /* if no character come in, assume EOF status */
       return 1;
}


/*
   Wait for the 'string' to come in on Port.

   return value :
        -1      : failed
         0      : found
         others : not found!

   NOTES :
   1. Wait for up 'MaxTime' 1/18 second for the string to arrive.
   2. If mode is 0, case sensitive.
   3. If mode is 1, not case sensitive.
 */

int comm_waitFor(COMM *Port,char *string,int MaxTime,int mode)
{
char               ch;
char              *chrPtr;

    /* not opened */
    if ( !Port )
        return -1;

    /* starting address */
    chrPtr = string;

    /* set timer, and starting to count down */
    timerSet( MaxTime );

    /* keep on comparing until following two condition were meet */
    /* 1) end of string */
    /* 2) time is up */
    while( *chrPtr && timerIsNotUp() )
    {
        /* character available in input buffer */

        if ( ((Port)->inNum) )
        {
             ch = comm_getc( Port );      /* fetch one character */

             if ( mode )
             {

                /* not case sensitive */

                if ( toupper(*chrPtr) == toupper(ch) )
                    /* same character, compare next character */
                    chrPtr++;
                else
                    /* not the same, start all over again */
                    chrPtr=string;
             }
             else
             {
                /* case sensitive */

                if ( *chrPtr == ch )
                    /* same character, compare next character */
                    chrPtr++;
                 else
                    /* not the same, start all over again */
                    chrPtr=string;
             }
        }
    }

    timerUnSet();
    /* return 0 --- string was found */
    /* others   --- not got it. */
    return (int)(*chrPtr);
}


/*
   Wait for 'MaxTime' 1/18 second without any characters arriving at Port.

   NOTES :
   1. If mode is 0, any characters to do arrive during the execution
        of this routine are discarded and the input buffer for the given port
        is empty when this routine returns.
   2. If mode is 1, characters arriving at the port are detected but not
        discarded.
   3. Be careful of buffer-overflow if you use mode 1.
*/

void comm_waitQuiet(COMM *Port,int MaxTime,int mode)
{
int     count;

         /* if port not opened */
         if ( !Port )
             return;

         /* set timer, and start to count down */
         timerSet( MaxTime );

         if ( mode == 0 )
         {
             /* discard input buffer */

             while ( timerIsNotUp() )
             {
                  /* if any character come in */
                  /* reset timer, and start all over again */
                  if ( comm_getc(Port) != -1 )
                     timerSet( MaxTime );       /* reset timer */
             }
         }
         else
         {
             /* keep input buffer */

             count=((Port)->inNum);     /* number of character in input buffer */

             /* wait until time is up */
             while( timerIsNotUp() )
             {
                 if ( ((Port)->inNum) != count )
                 {
                    /* if any character come in */
                    /* reset timer, and start all over again */
                    timerSet( MaxTime );       /* reset timer */
                    count = ((Port)->inNum);   /* reset counter */
                 }
             }
         }

         timerUnSet();

         return;
}

/*
   Turn on the BREAK signal for 'MaxTime' 1/18 second.
*/

int comm_break( COMM *Port,int MaxTime )
{
register BYTE      RegLCR;

     /* if port not opened */
     if ( !Port )
        return -1;

     comm_setBreak( Port );

     /* set timer, start to count down */
     timerSet( MaxTime );
     while( timerIsNotUp() );           /* wait until time is up */

     comm_resetBreak( Port );

     timerUnSet();

     return 0;
}


/*
   Flush input buffer
   return value :
        -1 : failed
         0 : OK
*/

int comm_inClear(register COMM *Port)
{
       /* if port not opened */
       if ( !Port )
           return -1;

       /* disable interrupt to avoid collision */
       disable();

       /* initialize input buffer */
       Port->inQueFirst = Port->inQue;
       Port->inQueLast  = Port->inQue;
       Port->inNum      = 0;

       /* enable interrupt */
       enable();

       return 0;
}


/*
   Flush the output buffer
   return value :
        -1 : failed
         0 : OK
 */

int comm_outClear(register COMM *Port)
{
     if ( !Port )
         return -1;

     /* disable interrupt to avoid collision */
     disable();

     /* initialize output buffer */
     Port->outQueFirst = Port->outQue;
     Port->outQueLast  = Port->outQue;
     Port->outNum      = 0;

     /* enable interrupt */
     enable();

     return 0;
}

