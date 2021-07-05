#include "Control.h"
#include <stdio.h>
#include "Packet.h"

Control* Control::instance = NULL;

Control::Control()
{
	// 내 컴퓨터		: 192.168.0.94
	// 강사님 컴퓨터	: 192.168.0.93
	Client.CreateSocket("192.168.0.94", 9000);
}

void Control::InsertMember()
{
	char Name[20], ID[10], PW[10];
	int Age;

	printf("이름 : ");			gets_s(Name, sizeof(Name));
	printf("아이디 : ");			gets_s(ID, sizeof(ID));
	printf("패스워드 : ");		gets_s(PW, sizeof(PW));
	printf("나이 : ");			scanf_s("%d", &Age);
	char dummy = getchar();

	// 서버 전송 
	// 1. 패킷 생성
	NEWMEMBER pack = pack_NewMember(Name, ID, PW, Age);
	// 2. 전송
	Client.SendData((const char*)&pack, sizeof(pack));
}

void Control::Login()
{
	char ID[10], PW[10];
	printf("아이디 : ");			gets_s(ID, sizeof(ID));
	printf("패스워드 : ");		gets_s(PW, sizeof(PW));
	
	// 서버 전송
	LOGIN pack = pack_Login(ID, PW);
	Client.SendData((const char*)&pack, sizeof(pack));
}

void Control::Logout()
{
	char ID[10];
	printf("아이디 : ");			gets_s(ID, sizeof(ID));

	// 서버 전송
	LOGIN pack = pack_Logout(ID);
	Client.SendData((const char*)&pack, sizeof(pack));
}

void Control::RecvData(const char* msg, int size)
{
	printf(">> [수신데이터] %dbyte\n", size);

	int* p = (int*)msg;

	if (*p == ACK_NEWMEMBER_S)
	{
		printf(">> 회원가입 성공\n");
	}
	else if (*p == ACK_NEWMEMBER_F)
	{
		printf(">> 회원가입 실패\n");
	}
	else if (*p == ACK_LOGIN_S)
	{
		printf(">> 로그인 성공\n");
	}
	else if (*p == ACK_LOGIN_F)
	{
		printf(">> 로그인 실패\n");
	}
	else if (*p == ACK_LOGOUT_S)
	{
		printf(">> 로그아웃 성공\n");
	}
	else if (*p == ACK_LOGOUT_F)
	{
		printf(">> 로그아웃 실패\n");
	}
}