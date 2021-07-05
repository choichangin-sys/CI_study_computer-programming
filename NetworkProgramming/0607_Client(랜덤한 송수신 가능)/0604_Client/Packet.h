#pragma once
/*
	App �������� ����
	1. ��Ŷ ���� define
	2. ��Ŷ�� ���� ����ü ���� (ù ��° ����� flag���ǰ� �߿�.)
*/
// ����ü�� ���� ��Ģ�� 1����Ʈ�� �Ѵٴ� �ǹ�
//#pragma pack(1)
#define PACK_NEWMEMBER	1
#define PACK_LOGIN		2
#define PACK_LOGOUT		2

#define ACK_NEWMEMBER_S 10
#define ACK_NEWMEMBER_F 11

#define ACK_LOGIN_S		12
#define ACK_LOGIN_F		13

#define ACK_LOGOUT_S		14
#define ACK_LOGOUT_F		15


// �� ����� ���ƾ���.
typedef struct tagNewMember
{
	int flag; // �߿���.
	char name[20];
	char id[10];
	char pw[10];
	int age;
}NEWMEMBER;

typedef struct tagLogin
{
	int flag;
	char name[20];
	char id[10];  // ������ ����ϴ� ��
	char pw[10];  // ������ ����ϴ� ��
	int age;
}LOGIN;

NEWMEMBER pack_NewMember(const char* name, const char* id, const char* pw, int age);

LOGIN pack_Login(const char* id, const char* pw);
LOGIN pack_Logout(const char* id);