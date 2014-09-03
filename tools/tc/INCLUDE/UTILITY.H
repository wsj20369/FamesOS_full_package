/*
  ┌──────────────────────────┐
  │  書名 :   TURBO C 通訊程式設計 ----技巧與實務      │
  │  作者 :   楊玄周 楊玄彰                            │
  │  出版 :   波全資訊股份有限公司                     │
  └──────────────────────────┘
*/
typedef unsigned char BYTE;
typedef unsigned      WORD;
typedef unsigned      BOOL;

#define TRUE         1
#define FALSE        0
#define ON           1
#define OFF          0
#define OK           0
#define FAIL         1

void    changeScreen( int x1, int y1, int x2, int y2 , BOOL Saving );
void    restoreScreen( BOOL Saving );
void    mainScreen();
void    prompt( char *pStr );
void    message( char *pStr );
void    beep( int frequency, int duration );
void    ask( int x, int y, char *askMessage, char *buffer );
char    queryCharBox( char *askMessage, char *validString );
void    queryStringBox( char *askMessage, char *buffer );
char    getCharValid( char *validString );

void    timerSet( int count );
void    timerUnSet( void );
BOOL    timerInUse( void );
BOOL    timerIsUp( void );
BOOL    timerIsNotUp( void );

void    interrupt       breakISR( void );
void    breakInstall( void );
void    breakUnInstall( void );
BOOL    breakPressed( void );
void    breakReset( void );


