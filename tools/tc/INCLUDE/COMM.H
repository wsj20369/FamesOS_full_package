
/*
  ┌──────────────────────────┐
  │  書名 :   TURBO C 通訊程式設計 ----技巧與實務      │
  │  作者 :   楊玄周 楊玄彰                            │
  │  出版 :   波全資訊股份有限公司                     │
  └──────────────────────────┘
*/
/*
        COMM.H

   definition for communication protocol

   Layout of LCR(Line Control Register)
        BIT 0-1 : data bit
                7 bits --- 10
                8 bits --- 11
        BIT 2   : stop bit
                1 bit  --- 0
                2 bit  --- 1
        BIT 3-5 : parity
                NO     --- 000          ignore
                ODD    --- 001
                EVEN   --- 011
                MARK   --- 101          always ON
                SPACE  --- 111          always OFF
*/
#define COM1            1       /* port */
#define COM2            2

#define BIT7            2       /* data bit */
#define BIT8            3

#define STOP1           0       /* stop bit */
#define STOP2           4

#define PARITY_NONE     0       /* parity */
#define PARITY_ODD      8
#define PARITY_EVEN     24
#define PARITY_MARK     40
#define PARITY_SPACE    56

/* register name for 8250 UART */
#define DATA            0       /* data register */
#define BAUDL           0       /* baud rate divisor (LSB) */
#define IER             1       /* Interrupt Enable Register */
#define BAUDH           1       /* baud rate divisor (MSB) */
#define IIR             2       /* Interrupt Identification Register */
#define LCR             3       /* Line Control Register */
#define MCR             4       /* Modem Control Register */
#define LSR             5       /* Line Status Register */
#define MSR             6       /* Modem Status Register */


/* data structure definition for communication port */
typedef struct
{
    /* I/O address */
    unsigned       base;       /* base address of I/O address for async port */
    unsigned char  RegMSR;
    unsigned char  RegLSR;
    unsigned       TxDelay;

    /* input buffer */
    unsigned char *inQue;      /* starting address for input buffer */
    unsigned char *inQueStop;  /* signal for 'end of buffer' */
    unsigned char *inQueFirst; /* where to put into the buffer by other end */
    unsigned char *inQueLast;  /* where to get from the buffer by ourself */
    unsigned       inNum;      /* number of characters in input buffer */
    /* output buffer */
    unsigned char *outQue;     /* starting address for output buffer */
    unsigned char *outQueStop; /* signal for 'end of buffer' */
    unsigned char *outQueFirst;/* where to put into the buffer by ourself */
    unsigned char *outQueLast; /* where to get from the buffer by other end */
    unsigned       outNum;     /* number of characters in output buffer */
    /* xon/xoff handshake protocol */
    unsigned char  sentXoff;   /* TRUE if an XOFF has been sent */
    unsigned char  lookXoff;   /* TRUE if we must recognize Xon/Xoff */
    unsigned char  recvXoff;   /* TRUE if we received an XOFF */
} COMM;


/* detecting & setting signal status */
void     comm_setDTR( COMM *Port );     /* set DTR on */
void     comm_resetDTR( COMM *Port );   /* set DTR off */
void     comm_setBreak( COMM *Port );   /* set Break on */
void     comm_resetBreak( COMM *Port ); /* set Break off */
BOOL     comm_isDTR( COMM *Port );      /* MCR bit 0 --- 0x01 */
BOOL     comm_isBreak( COMM *Port );    /* LCR bit 6 --- 0x40 */
BOOL     comm_isDCD( COMM *Port );      /* MSR bit 7 --- 0x80 */
BOOL     comm_isRing( COMM *Port );     /* MSR bit 6 --- 0x40 */

/* detecting & setting a register contents */
int      comm_getStatus(COMM *Port,int UARTregister);
void     comm_setStatus(COMM *Port,int UARTregister, int newStatus);

/* open a commnunication port, including
   communication protocol setup
   including port, baud rate, parity, data bit, stop bit. */
int      comm_setBaud( COMM *Port, int baud );  /* baud rate setup */
int      comm_params(COMM *Port, int baud, int parity, int dataBit,
         int stopBit);                          /* protocol setup */
int      comm_portNum(COMM *Port);              /* return port number */

/* 1. parameter setting
   2. input/output buffer setting
   3. install new ISR(Interrupt Service Routine), memorize old ISR.
   4. enable interrupt */
COMM    *comm_open(int port,int baud,int parity,int dataBit,
               int stopBit,int inQuesize,int outQuesize);
/* close a communication port, including
   1. release input/output buffer
   2. release ISR, and restore old ISR. */
void     comm_close(COMM *Port);


/*
   NOTES:
   Here, we try to implement a character stream for communication port,
        similiar to file stream we have in standard C library.

   Therefore, we implement several function call, which name is almost the
        same as file stream.
*/


/* return current available character in input/ouput buffer */
unsigned comm_inNUM( COMM *Port );
unsigned comm_outNUM( COMM *Port );

/* flush input/output buffer */
int      comm_inClear(COMM *Port);
int      comm_outClear(COMM *Port);

/* data transmission, character stream. */
char     comm_putc(COMM *Port, char  ch );      /* send a character */
int      comm_puts(COMM *Port, char *string );  /* send a string */
char     comm_getc(COMM *Port );                /* receive a character */
BOOL     comm_inkey(COMM *Port, char *ch );
         /* receive a string for maximum length 'maxLen' at 'maxTime' */
char    *comm_gets(COMM *Port,char *string,int maxLen,int maxTime );
         /* push a character back to input buffer */
char     comm_ungetc(COMM *Port, char ch );

         /* read number 'num' of size 'size' string from input buffer at maxTime */
int      comm_read(COMM *Port,char *buffer,int size,int num,int maxTime );
         /* write number 'num' of size 'size' string to output buffer */
int      comm_write(COMM *Port,char *buffer,int size,int num );
         /* formatted output & variable argument */
int      comm_printf(COMM *Port,char *format,... );
         /* wait for character to come in, if no character coming, we assume EOF */
int      comm_eof(COMM *Port,int maxTime );

int      comm_waitFor(COMM *Port,char *string,int MaxTime,int mode);
void     comm_waitQuiet(COMM *Port,int MaxTime,int mode);

/* send a break signal to other end */
int      comm_break(COMM *Port,int count);


