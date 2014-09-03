typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;

/* �߼������� */
#define  RY_FIND                1       /*���� */
#define  RY_FIND_NEXT           2       /*����һ��*/
#define  RY_OPEN                3       /*����*/
#define  RY_CLOSE               4       /*�ر���*/
#define  RY_READ                5       /*����*/
#define  RY_WRITE               6       /*д��*/
#define  RY_RANDOM              7       /*���������*/
#define  RY_SEED                8       /*����������*/
#define  RY_WRITE_USERID        9       /*д�û� ID*/
#define  RY_READ_USERID         10      /*���û� ID*/
#define  RY_SET_MOUDLE          11      /*����ģ����*/
#define  RY_CHECK_MOUDLE        12      /*���ģ��״̬*/
#define  RY_WRITE_ARITHMETIC    13      /*д�㷨*/
#define  RY_CALCULATE1          14      /*���� 1*/
#define  RY_CALCULATE2          15      /*���� 2*/
#define  RY_CALCULATE3          16      /*���� 3*/
#define  RY_DECREASE            17      /*�ݼ�ģ�鵥Ԫ*/

/* ������
#define  ERR_SUCCESS                0       /*û�д���*/
#define  ERR_NO_PARALLEL_PORT       1       /*�˻�û�в���*/
#define  ERR_NO_DRIVER              2       /*û��װ��������*/
#define  ERR_NO_ROCKEY              3       /*������û�� Rockey ��*/
#define  ERR_INVALID_PASSWORD       4       /*�������� Rockey ��, ����������(pass1, pass2)��*/
#define  ERR_INVALID_PASSWORD_OR_ID 5       /*����������Ӳ�� ID*/
#define  ERR_SETID                  6               /*����Ӳ�� ID ��*/
#define  ERR_INVALID_ADDR_OR_SIZE   7       /*��д��ַ�򳤶�����*/
#define  ERR_UNKNOWN_COMMAND        8       /*û�д�����*/
#define  ERR_NOTBELEVEL3            9       /*�ڲ�����*/
#define  ERR_READ                   10      /*�����ݴ�*/
#define  ERR_WRITE                  11      /*д���ݴ�*/
#define  ERR_RANDOM                 12      /*�������*/
#define  ERR_SEED                   13      /*�������*/
#define  ERR_CALCULATE              14      /*�����*/
#define  ERR_NO_OPEN                15      /*�ڲ���ǰû�д���*/
#define  ERR_OPEN_OVERFLOW          16      /*�򿪵���̫��(>16)*/
#define  ERR_NOMORE                 17      /*�Ҳ����������*/
#define  ERR_NEED_FIND              18      /*û�� Find ֱ������ FindNext*/
#define  ERR_DECREASE               19      /*�ݼ���*/

#define  ERR_AR_BADCOMMAND          20      /*�㷨ָ���*/
#define  ERR_AR_UNKNOWN_OPCODE      21      /*�㷨�������*/
#define  ERR_AR_WRONGBEGIN          22      /*�㷨��һ��ָ��г���*/
#define  ERR_AR_WRONG_END           23      /*�㷨���һ��ָ��г���*/
#define  ERR_AR_VALUEOVERFLOW       24      /*�㷨�г���ֵ > 63*/
#define  ERR_UNKNOWN                0xffff      /*δ֪����*/

#define  ERR_RECEIVE_NULL           0x100       /*���ղ���*/
#define  ERR_PRNPORT_BUSY           0x101       /*��ӡ��æ*/
#define  ERR_UNKNOWN_SYSTEM         0x102

/* ������ʽ:
(1) ������
    �������:
    function = 0
    *p1 = pass1
    *p2 = pass2
    *p3 = pass3
    *p4 = pass4
    ����:
    *lp1 Ϊ����Ӳ�� ID
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(2) ������һ��
    �������:
    function = 1
    *p1 = pass1
    *p2 = pass2
    *p3 = pass3
    *p4 = pass4
    ����:
    *lp1 Ϊ����Ӳ�� ID
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(3) ����
    �������:
    function = 2
    *p1 = pass1
    *p2 = pass2
    *p3 = pass3
    *p4 = pass4
    *lp1 = Ӳ�� ID
    ����:
    *handle Ϊ���ľ��
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(4) �ر���
    �������:
    function = 3
    *handle = ���ľ��
    ����:
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(5) ����
    �������:
    function = 4
    *handle = ���ľ��
    *p1 = pos
    *p2 = length
    buffer = ��������ָ��
    ����:
    buffer ��������������
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(6) д��
    function = 5
    *handle = ���ľ��
    *p1 = pos
    *p2 = length
    buffer = ��������ָ��
    ����:
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(7) �����
    function = 6
    *handle = ���ľ��
    ����:
    *p1 = �����
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������
    
(8) ������
    function = 7
    *handle = ���ľ��
    *lp2 = ������
    ����:
    *p1 = ������1
    *p2 = ������2
    *p3 = ������3
    *p4 = ������4
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(9) д�û� ID [*]
    function = 8
    *handle = ���ľ��
    *lp1 = �û� ID
    ����:
    ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(10) ���û� ID
     function = 9
     *handle = ���ľ��
     ����:
     *lp1 = �û� ID
     ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(11) ����ģ�� [*]
     function = 10
     *handle = ���ľ��
     *p1 = ģ���
     *p2 = �û�ģ������
     *p3 = �Ƿ������ݼ� (1 = ����, 0 = ������)
     ����:
     ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(12) ���ģ���Ƿ���Ч
     function = 11
     *handle = ���ľ��
     *p1 = ģ���
     ����:
     *p2 = 1 ��ʾ��ģ����Ч
     *p3 = 1 ��ʾ��ģ����Եݼ�
     ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(13) д�㷨 [*]
     function = 12
     *handle = ���ľ��
     *p1 = pos
     buffer = �㷨ָ�
     ����:
     ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������
     
(14) ����1 (ģ����, ID ��λ, ID ��λ, �����)
     function = 13
     *handle = ���ľ��
     *lp1 = ������ʼ��
     *lp2 = ģ���
     *p1 = ����ֵ1
     *p2 = ����ֵ2
     *p3 = ����ֵ3
     *p4 = ����ֵ4
     ����:
     *p1 = ����ֵ1
     *p2 = ����ֵ2
     *p3 = ����ֵ3
     *p4 = ����ֵ4
     ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(15) ����2
     function = 14
     *handle = ���ľ��
     *lp1 = ������ʼ��
     *lp2 = ������
     *p1 = ����ֵ1
     *p2 = ����ֵ2
     *p3 = ����ֵ3
     *p4 = ����ֵ4
     ����:
     *p1 = ����ֵ1
     *p2 = ����ֵ2
     *p3 = ����ֵ3
     *p4 = ����ֵ4
     ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(16) ����3
     function = 15
     *handle = ���ľ��
     *lp1 = ������ʼ��
     *lp2 = ������ʼ��ַ
     *p1 = ����ֵ1
     *p2 = ����ֵ2
     *p3 = ����ֵ3
     *p4 = ����ֵ4
     ����:
     *p1 = ����ֵ1
     *p2 = ����ֵ2
     *p3 = ����ֵ3
     *p4 = ����ֵ4
     ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������

(17) �ݼ�
     function = 16
     *handle = ���ľ��
     *p1 = ģ���
     ����Ϊ 0 ��ʾ�ɹ�, ����Ϊ������
*/

WORD far Rockey(WORD function, WORD far* handle, DWORD far* lp1,  DWORD far* lp2, WORD far* p1, WORD far* p2, WORD far* p3, WORD far* p4, BYTE far* buffer);
