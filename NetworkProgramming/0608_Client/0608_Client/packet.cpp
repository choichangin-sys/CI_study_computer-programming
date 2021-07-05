//packet.cpp : 모든 소스파일은 pch.h 파일을 제일 먼저 include 해야한다.

#include "pch.h"    // pre complie header
#include "packet.h"


PACKETNEWMEMBER PACKETNEWMEMBER::CreatePacket(const char* _Name,
	const char* _ID,
	const char* _PW)
{
	PACKETNEWMEMBER packet;

	packet.flag = PACK_NEWMEMBER;
	strcpy_s(packet.Name, sizeof(packet.Name), _Name);
	strcpy_s(packet.ID, sizeof(packet.ID), _ID);
	strcpy_s(packet.PW, sizeof(packet.PW), _PW);

	return packet;
}

PACKETNEWMEMBER PACKETNEWMEMBER::CreatePacket(const char* _ID,
											  const char* _PW)
{
	PACKETNEWMEMBER packet;

	packet.flag = PACK_LOGIN;
	strcpy_s(packet.ID, sizeof(packet.ID), _ID);
	strcpy_s(packet.PW, sizeof(packet.PW), _PW);

	return packet;
}

