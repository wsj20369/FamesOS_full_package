
/*
  ┌──────────────────────────┐
  │  書名 :   TURBO C 通訊程式設計 ----技巧與實務      │
  │  作者 :   楊玄周 楊玄彰                            │
  │  出版 :   波全資訊股份有限公司                     │
  └──────────────────────────┘
*/
#define    CommandPrefix     "AT"
#define    QuietCommand      "Q0"
#define    EndOfCommand      "\r"
#define    DialToneCommand   "DT"
#define    DialPulseCommand  "DP"
#define    AnswerCommand     "A"
#define    ResetCommand      "Z"
#define    OnHookCommand     "H0"
#define    OffHookCommand    "H1"
#define    EndDialCommand    ""
#define    InitialCommand    "&C1&D2X4S0=0M0"

/* Modem Response */
#define    ModemSuccess           0
#define    ModemConnect300        1
#define    ModemRing              2
#define    ModemNoDCD             3
#define    ModemCommandError      4
#define    ModemConnect1200       5
#define    ModemNoTone            6
#define    ModemBusy              7
#define    ModemNoAnswer          8
#define    ModemNotUsed           9
#define    ModemConnect2400       10
#define    ModemNoRing            11
#define    ModemInvalidMessage    12
#define    ModemUserCancel        13


/* Command ProtoType */
void    modemCommand( char *command );
void    initialModem( void );
char    *strSubMatch( char *mainString, char *subString );
int     modemReturnCode( void );
int     modemWaitDCD( void );
int     dial( char *phoneNumber );
BOOL    modemFetchResponse( int numChar );
int     modemResponse( void );
int     answer( void );
int     autoAnswer( void );
BOOL    modemCommandState( void );
BOOL    modemCommandRetry( char *sPtr, int retry );
BOOL    modemHangUp( void );
