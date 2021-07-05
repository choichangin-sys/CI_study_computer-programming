#pragma once

#define PACK_NEWMEMBER	1
#define PACK_LOGIN		2

#define ACK_NEWMEMBER_S 10
#define ACK_NEWMEMBER_F 11

#define ACK_LOGIN_S		12
#define ACK_LOGIN_F		13

// 두 사이즈가 같아야함.
typedef struct tagNewMember
{
	int flag; // 중요함.
	char name[20];
	char id[10];
	char pw[10];
	int age;
}NEWMEMBER;

typedef struct tagLogin
{
	int flag;
	char name[20];
	char id[10];  // 실제로 사용하는 것
	char pw[10];  // 실제로 사용하는 것
	int age;
}LOGIN;