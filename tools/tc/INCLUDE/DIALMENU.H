/*
  ┌──────────────────────────┐
  │  書名 :   TURBO C 通訊程式設計 ----技巧與實務      │
  │  作者 :   楊玄周 楊玄彰                            │
  │  出版 :   波全資訊股份有限公司                     │
  └──────────────────────────┘
*/
/*
   Data for communication port we using right now.
        including port number, baud rate, parity, data bits,
                  stop bit
        and the data structure used for the library in COMM.C
*/
extern  COMM    *Port;
extern  int     commPort;
extern  int     baudrate;
extern  int     parity;
extern  int     dataBit;
extern  int     stopBit;


/* echo mode setting */
#define EchoCODES     3            /* 3 type of echo setting */
#define NO_ECHO       0            /* no echo */
#define LOCAL_ECHO    1            /* local echo */
#define REMOTE_ECHO   2            /* local & remote echo */

/* history buffer size (2K) */
#define HistorySIZE   2048         /* 2**11 */
#define HistoryMASK   0x3FF        /* checking end of buffer */


/*
   Variable used for showing status.
        including history, cpature, echo, online,
                  special character
*/
extern  BOOL    newstatus;            /* status area updated? */
extern  BOOL    online;               /* online? */
extern  BYTE    history[HistorySIZE]; /* history buffer */
extern  int     HisPointer;           /* history buffer index */
extern  int     captureHandle;        /* capture file handle */
extern  BOOL    Cr_To_CrLF;           /* convert CR to CR_LF */
extern  BOOL    SpecialCharacter;     /* xform speicial char */
extern  int     echo;                 /* echo mode */
extern  char    *EchoName[EchoCODES]; /* name of echo mode */


/* prototype function declaraction */
void    dialmenu( void );
void    StatusArea( void );
int     modemStartUp( void );

