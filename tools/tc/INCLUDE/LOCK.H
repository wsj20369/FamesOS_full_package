//Lock.h文件
//程序中对加密锁操作时，需包含本文件
#include "RYTC20.H"
WORD Handle;
DWORD lp1;
DWORD lp2;
WORD p1=0xBFEF;
WORD p2=0x737F;
WORD p3=0x0000;
WORD p4=0x0000;
BYTE buffer[1024];


//查找加密锁
//返回：0表示未找到，1表示找到。成功时lp1为加密锁的硬件ID。
int FindLock()
{
    WORD Function=RY_FIND;
	WORD RetResult;
	RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
	if(RetResult)
		return 0;
	return 1;
}


//打开加密锁，对加密锁读写操作必须先打开锁
//返回：0表示未能打开，1表示打开
int OpenLock()
{
	WORD Function=RY_OPEN;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}


//对加密锁用户读写区进行写操作
//调用时，需设置p1,p2,buffer。p1为写的起始位置,p2为写的字节数,buffer为被写缓冲区的首指针。
//返回：0表示写失败，1表示写成功。
int WriteLock()
{
    WORD Function=RY_WRITE;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}

//对加密锁用户读写区进行读操作
//调用时，需设置p1,p2。p1为读的起始位置,p2为读的字节数。
//返回：0表示写失败，1表示写成功。成功时buffer为接收缓冲区的首指针。
int ReadLock()
{
    WORD Function=RY_READ;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}

//读出用户定义的ID
//返回：0表示读失败，1表示读成功。成功时lp1为用户ID。
int ReadUserID()
{
	WORD Function=RY_READ_USERID;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}
//关闭锁，对锁操作完应及时关闭
//返回：0表示失败，1表示成功。
int CloseLock()
{
	WORD Function=RY_CLOSE;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}