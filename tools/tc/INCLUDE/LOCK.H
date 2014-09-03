//Lock.h�ļ�
//�����жԼ���������ʱ����������ļ�
#include "RYTC20.H"
WORD Handle;
DWORD lp1;
DWORD lp2;
WORD p1=0xBFEF;
WORD p2=0x737F;
WORD p3=0x0000;
WORD p4=0x0000;
BYTE buffer[1024];


//���Ҽ�����
//���أ�0��ʾδ�ҵ���1��ʾ�ҵ����ɹ�ʱlp1Ϊ��������Ӳ��ID��
int FindLock()
{
    WORD Function=RY_FIND;
	WORD RetResult;
	RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
	if(RetResult)
		return 0;
	return 1;
}


//�򿪼��������Լ�������д���������ȴ���
//���أ�0��ʾδ�ܴ򿪣�1��ʾ��
int OpenLock()
{
	WORD Function=RY_OPEN;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}


//�Լ������û���д������д����
//����ʱ��������p1,p2,buffer��p1Ϊд����ʼλ��,p2Ϊд���ֽ���,bufferΪ��д����������ָ�롣
//���أ�0��ʾдʧ�ܣ�1��ʾд�ɹ���
int WriteLock()
{
    WORD Function=RY_WRITE;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}

//�Լ������û���д�����ж�����
//����ʱ��������p1,p2��p1Ϊ������ʼλ��,p2Ϊ�����ֽ�����
//���أ�0��ʾдʧ�ܣ�1��ʾд�ɹ����ɹ�ʱbufferΪ���ջ���������ָ�롣
int ReadLock()
{
    WORD Function=RY_READ;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}

//�����û������ID
//���أ�0��ʾ��ʧ�ܣ�1��ʾ���ɹ����ɹ�ʱlp1Ϊ�û�ID��
int ReadUserID()
{
	WORD Function=RY_READ_USERID;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}
//�ر���������������Ӧ��ʱ�ر�
//���أ�0��ʾʧ�ܣ�1��ʾ�ɹ���
int CloseLock()
{
	WORD Function=RY_CLOSE;
    WORD RetResult;
    RetResult= Rockey(Function,&Handle,&lp1,&lp2, &p1, &p2, &p3, &p4, buffer);
    if(RetResult)
		return 0;
	return 1;
}