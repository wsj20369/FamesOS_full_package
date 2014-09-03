/*
  �z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{
  �x  �ѦW :   TURBO C �q�T�{���]�p ----�ޥ��P���      �x
  �x  �@�� :   ���ȩP ���ȹ�                            �x
  �x  �X�� :   �i����T�ѥ��������q                     �x
  �|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}
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