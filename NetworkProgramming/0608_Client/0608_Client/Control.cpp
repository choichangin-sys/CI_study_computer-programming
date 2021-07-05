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
	printf(">> [���ŵ�����] %dbyte\n", size);
	int* p = (int*)msg;
	
	if (*p == ACK_NEWMEMBER_S)
	{
		MessageBox(0, ">> ȸ������ ���� <<", "�˸�", MB_OK);
	}
	else if (*p == ACK_NEWMEMBER_F)
	{
		MessageBox(0, ">> ȸ������ ���� <<", "�˸�", MB_OK);
	}
	else if (*p == ACK_LOGIN_S)
	{
		MessageBox(0, ">> �α��� ���� <<", "�˸�", MB_OK);
		// ���������� �ؾ��� ���� ����. 
		// ��ȭâ���� �Ѿ����.
		// ��޷� ä��ȭ�� ����
		PACKETLOGIN* pLogin = (PACKETLOGIN*)msg;

		// �ڽ��� ������� HIDE
		pForm->ShowWindow(SW_HIDE);
		CChatDlg dlg;
		dlg.SendData(pLogin->Name);
		dlg.DoModal();

		pForm->ShowWindow(SW_NORMAL); //SW_SHOW
		pForm->ShowWindow(SW_SHOW);
	}
	else if (*p == ACK_LOGIN_F)
	{
		MessageBox(0, ">> �α��� ���� <<", "�˸�", MB_OK);
	}
	
}

void Control::InsertMember(const char* ID, const char* PW, const char* Name)
{
	//���� ����(1. ��Ŷ ����, 2. ����)
	PACKETNEWMEMBER pack = PACKETNEWMEMBER::CreatePacket(ID, PW, Name);
	client.SendData((const char*)&pack, sizeof(pack));
}

void Control::LoginMember(const char* ID, const char* PW)
{
	//���� ����(1. ��Ŷ ����, 2. ����)
	PACKETLOGIN pack = PACKETLOGIN::CreatePacket(ID, PW);
	client.SendData((const char*)&pack, sizeof(pack));
}
