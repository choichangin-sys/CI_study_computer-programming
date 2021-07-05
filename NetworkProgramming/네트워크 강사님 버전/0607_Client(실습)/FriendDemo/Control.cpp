//control.cpp
#include "pch.h"
#include <stdio.h>
#include "FriendDemoDlg.h"

#include "Control.h"
#include "packet.h"


Control* Control::instance = NULL;

Control::Control()
{
	client.CreateSocket("192.168.0.93", 9000);
}

void Control::ParentForm(CFriendDemoDlg* pDlg)
{
	pForm = pDlg;
}

void Control::RecvData(const char* msg, int size)
{
	printf(">> [수신데이터] %dbyte\n", size);
	int* p = (int*)msg;
	if (*p == ACK_PERSON_S)
	{
		MessageBox(0, "알림", ">> 회원가입 성공", MB_OK);
	}
	else if (*p == ACK_PERSON_F)
	{
		MessageBox(0, "알림", ">> 회원가입 실패", MB_OK);
	}
	else if (*p == ACK_LISTALL)
	{
		printf(">> 회원 리스트 처리 성공\n");
		PACKLISTALL* plist = (PACKLISTALL*)msg;
		pForm->PersonList(plist);
	}
}

void Control::InsertMember(const char* name, int age, char gender)
{
	//서버 전송(1. 패킷 생성, 2. 전송)
	PACKETPERSON pack = pack_NewPerson(name, age, gender);
	client.SendData((const char*)&pack, sizeof(pack));
}

void Control::MemberList()
{	
	//서버 전송
	PACKLISTALL pack = pack_PersonList();
	client.SendData((const char*)&pack, sizeof(pack));
}