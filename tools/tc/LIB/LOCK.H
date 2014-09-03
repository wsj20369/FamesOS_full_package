#define   SUCCESSED  1
#define   FAILED  0
#include "RYTC20.H"
WORD Handle;
DWORD lp1;
DWORD lp2;
WORD p1=0xBFEF;
WORD p2=0x737F;
WORD p3=0x0000;
WORD p4=0x0000;
BYTE buffer[1024];



int FindLock()
{
    WORD Function=RY_FIND;
	WORD RetResult;
	RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
	if(RetResult)
		return FAILED;
	return SUCCESSED;
	
}



int OpenLock()
{
	WORD Function=RY_OPEN;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return FAILED;
	return SUCCESSED;
}



int WriteLock()
{
    WORD Function=RY_WRITE;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return FAILED;
	return SUCCESSED;
}

int ReadLock()
{
    WORD Function=RY_READ;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return FAILED;
	return SUCCESSED;
}

int ReadUserID()
{
	WORD Function=RY_READ_USERID;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return FAILED;
	return SUCCESSED;
}

int CloseLock()
{
	WORD Function=RY_CLOSE;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return FAILED;
	return SUCCESSED;
}