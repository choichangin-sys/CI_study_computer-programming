//packet.cpp

#include "pch.h"
#include "packet.h"

PACKETPERSON pack_NewPerson(const char* name, int age, char gender)
{
	PACKETPERSON packet;
	
	packet.flag = PACK_PERSON;
	packet.count = 1;
	strcpy_s(packet.per[0].name, sizeof(packet.per[0].name), name);
	packet.per[0].age = age;
	packet.per[0].gender = gender;

	return packet;
}

PACKLISTALL pack_PersonList()
{
	PACKLISTALL packet = { 0 };

	packet.flag = PACK_LISTALL;

	return packet;
}