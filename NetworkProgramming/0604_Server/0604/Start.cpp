#include <stdio.h>
#include <ws2tcpip.h>
#include "CMyNet.h"
#include <WinSock2.h> // 선언부
#pragma comment(lib, "ws2_32.lib") // dll import정보

void TestCode1();
void TestCode2();
void TestCode3();

int main()
{
	//TestCode1();
	//TestCode2();

	try
	{
		CMyNet Net;
		Net.CreateSocket(9000);
	}
	catch (const char* msg)
	{
		printf("에러 : %s", msg);
	}
	

	return 0;
}

void TestCode1()
{
	// 1. 라이브러리 초기화(winsock 2.2버전)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("원도우 소켓 초기화 실패\n");
		exit(-1);
	}

	// 문자열 주소 -> 정수(4Byte)
	const char* ipaddr = "230.200.12.5";
	//int numberaddr = inet_addr(ipaddr);
	unsigned int numberaddr;
	inet_pton(AF_INET, ipaddr, &numberaddr);
	/*
	AF_INET  = Protocol version 4 (IPv4)을 사용할 것인가?
	AF_INET6 = Protocol version 6 (IPv6)을 사용할 것인가?
	*/
	printf("%s -> %x%08x\n", ipaddr, numberaddr);

	/*
	inet_ntoa 대신 inet_ntop 사용 권장
	v4 or v6
	*/

	// 정수(4Byte) -> 문자열 주소
	IN_ADDR in_addr;
	in_addr.s_addr = numberaddr;
	char ipaddr1[30];
	inet_ntop(AF_INET, &(in_addr.s_addr), ipaddr1, INET_ADDRSTRLEN);
	printf("0x%08xd -> %s\n", numberaddr, ipaddr1);

	// 2. 라이브러리 해제
	WSACleanup();
}

void TestCode2()
{
	// 1. 라이브러리 초기화(winsock 2.2버전)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("원도우 소켓 초기화 실패\n");
		exit(-1);
	}

	unsigned short us = 0x1234;    // 2byte
	unsigned long ul = 0x12345678; // 4byte
	unsigned short n_us = htons(us); // 2byte
	unsigned long n_ul = htonl(ul);  // 4byte

	// Host(?) -> Net(Big endian)
	printf("0x%08x -> 0x%08x\n", us, htons(us));
	printf("0x%08x -> 0x%08x\n", ul, htonl(ul));

	// Net(Big endian) -> Host(?)
	printf("0x%08x -> 0x%08x\n", n_us, ntohs(n_us));
	printf("0x%08x -> 0x%08x\n", n_ul, ntohl(n_ul));

	// 2. 라이브러리 해제
	WSACleanup();
}

void TestCode3()
{
	// 1. 라이브러리 초기화(winsock 2.2버전)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("원도우 소켓 초기화 실패\n");
		exit(-1);
	}


	// 2. 라이브러리 해제
	WSACleanup();
}