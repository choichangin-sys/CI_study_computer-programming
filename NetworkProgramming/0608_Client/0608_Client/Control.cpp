//control.cpp
#include "pch.h"
#include <stdio.h>
#include "0608_ClientDlg.h" // <=====

#include "Control.h"
#include "packet.h"
#include "CChatDlg.h"
#include "CChatDlg.h"

Control* Control::instance = NULL;

Control::Control()
{
	client.CreateSocket("192.168.0.93", 9000);
}

void Control::ParentForm(CMy0608ClientDlg* pDlg) // <=====
{
	pForm = pDlg;
}

void Control::RecvData(const char* msg, int size)
{
	printf(">> [수신데이터] %dbyte\n", size);
	int* p = (int*)msg;
	
	if (*p == ACK_NEWMEMBER_S)
	{
		MessageBox(0, ">> 회원가입 성공 <<", "알림", MB_OK);
	}
	else if (*p == ACK_NEWMEMBER_F)
	{
		MessageBox(0, ">> 회원가입 실패 <<", "알림", MB_OK);
	}
	else if (*p == ACK_LOGIN_S)
	{
		MessageBox(0, ">> 로그인 성공 <<", "알림", MB_OK);
		// 실질적으로 해야할 일이 있음. 
		// 대화창으로 넘어가야함.
		// 모달로 채팅화면 생성
		PACKETLOGIN* pLogin = (PACKETLOGIN*)msg;

		// 자신의 윈도우는 HIDE
		pForm->ShowWindow(SW_HIDE);
		CChatDlg dlg;
		dlg.SendData(pLogin->Name);
		dlg.DoModal();

		pForm->ShowWindow(SW_NORMAL); //SW_SHOW
		pForm->ShowWindow(SW_SHOW);
	}
	else if (*p == ACK_LOGIN_F)
	{
		MessageBox(0, ">> 로그인 실패 <<", "알림", MB_OK);
	}
	
}

void Control::InsertMember(const char* ID, const char* PW, const char* Name)
{
	//서버 전송(1. 패킷 생성, 2. 전송)
	PACKETNEWMEMBER pack = PACKETNEWMEMBER::CreatePacket(ID, PW, Name);
	client.SendData((const char*)&pack, sizeof(pack));
}

void Control::LoginMember(const char* ID, const char* PW)
{
	//서버 전송(1. 패킷 생성, 2. 전송)
	PACKETLOGIN pack = PACKETLOGIN::CreatePacket(ID, PW);
	client.SendData((const char*)&pack, sizeof(pack));
}
