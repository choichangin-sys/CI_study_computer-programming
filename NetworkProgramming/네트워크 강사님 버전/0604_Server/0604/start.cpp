//start.cpp

#include <stdio.h>
#include "CMyNet.h"

void testcode2();

int main()
{
	try
	{
		CMyNet net;
		net.CreateSocket(9000);
	}
	catch (const char* msg)
	{
		printf("���� : %s\n", msg);
	}

	return 0;
}

#include <WinSock2.h>					//�����
#include <ws2tcpip.h>	//inet_pton
#pragma comment(lib, "ws2_32.lib")		//dll import����


//�ּҺ�ȯ(���ڿ� <-> ����)
void testcode1()
{
	//1. ���̺귯�� �ʱ�ȭ(Winsock 2.2����)
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		exit(-1);
	}
	
	//[���ڿ� �ּ� -> 4byte ����]
	const char* ipaddr = "230.200.12.5";
	//int numberaddr = inet_addr(ipaddr);
	//https://docs.microsoft.com/ko-kr/windows/win32/api/ws2tcpip/nf-ws2tcpip-inet_pton?f1url=%3FappId%3DDev16IDEF1%26l%3DKO-KR%26k%3Dk(inet_pton);k(DevLang-C%252B%252B);k(TargetOS-Windows)%26rd%3Dtrue
	unsigned int numberaddr;
	inet_pton(AF_INET, ipaddr, &numberaddr);
	printf("%s -> 0x%08x\n", ipaddr, numberaddr);

	//[4byte�� ���� -> ���ڿ� �ּ�]
	//inet_ntoa ��� inet_ntop ��� ����
	//-> v4 or v6
	IN_ADDR in_addr;
	in_addr.s_addr = numberaddr;
	//printf("0x%08xd -> %s\n", numberaddr, inet_ntoa(in_addr));
	char ipaddr1[30];
	inet_ntop(AF_INET, &(in_addr.s_addr), ipaddr1, INET_ADDRSTRLEN);
	printf("0x%08xd -> %s\n", numberaddr, ipaddr1);
	
	//2. ���̺귯�� ����
	WSACleanup();
}

//����Ʈ ����
void testcode2()
{
	//1. ���̺귯�� �ʱ�ȭ(Winsock 2.2����)
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		exit(-1);
	}

	unsigned short us	= 0x1234;		//2byte
	unsigned long ul	= 0x12345678;	//4byte
	unsigned short n_us = htons(us);	
	unsigned long n_ul	= htonl(ul);	

	//Host(?) -> Net(Big endian)
	printf("0x%08x -> 0x%08x\n", us, n_us);
	printf("0x%08x -> 0x%08x\n", ul, n_ul);

	//Net(Big) -> Host(?)
	printf("0x%08x -> 0x%08x\n", n_us, ntohs(n_us));
	printf("0x%08x -> 0x%08x\n", n_ul, ntohl(n_ul));

	//2. ���̺귯�� ����
	WSACleanup();
}