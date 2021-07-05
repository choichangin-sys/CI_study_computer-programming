#include <stdio.h>
#include <ws2tcpip.h>
#include "CMyNet.h"
#include <WinSock2.h> // �����
#pragma comment(lib, "ws2_32.lib") // dll import����

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
		printf("���� : %s", msg);
	}
	

	return 0;
}

void TestCode1()
{
	// 1. ���̺귯�� �ʱ�ȭ(winsock 2.2����)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		exit(-1);
	}

	// ���ڿ� �ּ� -> ����(4Byte)
	const char* ipaddr = "230.200.12.5";
	//int numberaddr = inet_addr(ipaddr);
	unsigned int numberaddr;
	inet_pton(AF_INET, ipaddr, &numberaddr);
	/*
	AF_INET  = Protocol version 4 (IPv4)�� ����� ���ΰ�?
	AF_INET6 = Protocol version 6 (IPv6)�� ����� ���ΰ�?
	*/
	printf("%s -> %x%08x\n", ipaddr, numberaddr);

	/*
	inet_ntoa ��� inet_ntop ��� ����
	v4 or v6
	*/

	// ����(4Byte) -> ���ڿ� �ּ�
	IN_ADDR in_addr;
	in_addr.s_addr = numberaddr;
	char ipaddr1[30];
	inet_ntop(AF_INET, &(in_addr.s_addr), ipaddr1, INET_ADDRSTRLEN);
	printf("0x%08xd -> %s\n", numberaddr, ipaddr1);

	// 2. ���̺귯�� ����
	WSACleanup();
}

void TestCode2()
{
	// 1. ���̺귯�� �ʱ�ȭ(winsock 2.2����)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
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

	// 2. ���̺귯�� ����
	WSACleanup();
}

void TestCode3()
{
	// 1. ���̺귯�� �ʱ�ȭ(winsock 2.2����)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		exit(-1);
	}


	// 2. ���̺귯�� ����
	WSACleanup();
}