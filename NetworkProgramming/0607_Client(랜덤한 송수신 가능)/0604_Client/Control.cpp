#include "Control.h"
#include <stdio.h>
#include "Packet.h"

Control* Control::instance = NULL;

Control::Control()
{
	// �� ��ǻ��		: 192.168.0.94
	// ����� ��ǻ��	: 192.168.0.93
	Client.CreateSocket("192.168.0.94", 9000);
}

void Control::InsertMember()
{
	char Name[20], ID[10], PW[10];
	int Age;

	printf("�̸� : ");			gets_s(Name, sizeof(Name));
	printf("���̵� : ");			gets_s(ID, sizeof(ID));
	printf("�н����� : ");		gets_s(PW, sizeof(PW));
	printf("���� : ");			scanf_s("%d", &Age);
	char dummy = getchar();

	// ���� ���� 
	// 1. ��Ŷ ����
	NEWMEMBER pack = pack_NewMember(Name, ID, PW, Age);
	// 2. ����
	Client.SendData((const char*)&pack, sizeof(pack));
}

void Control::Login()
{
	char ID[10], PW[10];
	printf("���̵� : ");			gets_s(ID, sizeof(ID));
	printf("�н����� : ");		gets_s(PW, sizeof(PW));
	
	// ���� ����
	LOGIN pack = pack_Login(ID, PW);
	Client.SendData((const char*)&pack, sizeof(pack));
}

void Control::Logout()
{
	char ID[10];
	printf("���̵� : ");			gets_s(ID, sizeof(ID));

	// ���� ����
	LOGIN pack = pack_Logout(ID);
	Client.SendData((const char*)&pack, sizeof(pack));
}

void Control::RecvData(const char* msg, int size)
{
	printf(">> [���ŵ�����] %dbyte\n", size);

	int* p = (int*)msg;

	if (*p == ACK_NEWMEMBER_S)
	{
		printf(">> ȸ������ ����\n");
	}
	else if (*p == ACK_NEWMEMBER_F)
	{
		printf(">> ȸ������ ����\n");
	}
	else if (*p == ACK_LOGIN_S)
	{
		printf(">> �α��� ����\n");
	}
	else if (*p == ACK_LOGIN_F)
	{
		printf(">> �α��� ����\n");
	}
	else if (*p == ACK_LOGOUT_S)
	{
		printf(">> �α׾ƿ� ����\n");
	}
	else if (*p == ACK_LOGOUT_F)
	{
		printf(">> �α׾ƿ� ����\n");
	}
}