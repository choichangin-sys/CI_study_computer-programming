//packet.h
#pragma once

#define PACK_NEWMEMBER	1  // 아이디, 패스워드, 이름
#define PACK_LOGIN		2  // 아이디, 패스워드

#define ACK_NEWMEMBER_S	11 // 나머지 정보는 echo
#define ACK_NEWMEMBER_F	12 // 나머지 정보는 echo
#define ACK_LOGIN_S		13 // 아이디, 패스워드, 이름
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

typedef PACKETNEWMEMBER PACKETLOGIN; // 이름만 바꾼 것 

// PACKLOGIN == PACKETNEWMEMBER
// 패킷정의
// 패킷 구조체 정의
// control:: 기능 함수 구현
// form에서 생성된 정보를 수신하는 기능 
// 패킷 생성
// myclient에게 전송 처리