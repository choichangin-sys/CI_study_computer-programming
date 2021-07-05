//packet.h
#pragma once

#define PACK_NEWMEMBER	1  // ���̵�, �н�����, �̸�
#define PACK_LOGIN		2  // ���̵�, �н�����

#define ACK_NEWMEMBER_S	11 // ������ ������ echo
#define ACK_NEWMEMBER_F	12 // ������ ������ echo
#define ACK_LOGIN_S		13 // ���̵�, �н�����, �̸�
#define ACK_LOGIN_F		14 // echo



struct PACKETNEWMEMBER
{
	int flag;
	char ID[10];
	char PW[10];
	char Name[20];

	static PACKETNEWMEMBER CreatePacket(const char* _Name,
										const char* _ID,
										const char* _PW);

	static PACKETNEWMEMBER CreatePacket(const char* _ID,
										const char* _PW);

};

typedef PACKETNEWMEMBER PACKETLOGIN; // �̸��� �ٲ� �� 

// PACKLOGIN == PACKETNEWMEMBER
// ��Ŷ����
// ��Ŷ ����ü ����
// control:: ��� �Լ� ����
// form���� ������ ������ �����ϴ� ��� 
// ��Ŷ ����
// myclient���� ���� ó��