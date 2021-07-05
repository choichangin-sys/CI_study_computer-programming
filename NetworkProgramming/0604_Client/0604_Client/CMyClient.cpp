#include "CMyClient.h"
#include <WinSock2.h> // �����
#pragma comment(lib, "ws2_32.lib") // dll import����
#include <stdio.h>
#include <ws2tcpip.h>

CMyClient::CMyClient()
{
	// 1. ���̺귯�� �ʱ�ȭ(winsock 2.2����)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		exit(-1);
	}
}

CMyClient::~CMyClient()
{
	// 2. ���̺귯�� ����
	WSACleanup();
}

void CMyClient::CreateSocket(const char* ip, int port)
{
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		throw "���� ���� ����";
	}

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	unsigned int numberaddr;
	inet_pton(AF_INET, ip, &numberaddr);
	addr.sin_addr.s_addr = numberaddr;
	int retval = connect(Socket, (SOCKADDR*)&addr, sizeof(addr));

	if (retval == SOCKET_ERROR)
	{
		throw "���� ���� ����";
	}

	/*
	char buf1[20] = "��â��~";
	retval = send(Socket, buf1, strlen(buf1), 0);

	// ����
	char buf2[20];
	// sock�� ����� �������κ��� ���޵� �޽����� �����ϰڴ�.
	// ��, ������ ���� sizeof(buf)�� ũ�⸦ �غ��߰�, �� ������ ������ġ�� ����.
	// ������ ���� ���� ���ŵ� byte ũ�⸦ Ȯ���� �� �ִ�.
	int retval2 = recv(Socket, buf2, sizeof(buf2), 0);
	if (retval2 == -1 || retval2 == 0)
	{
		printf("���� ���� or ������ ������\n");
		return;
	}

	buf2[retval2] = '\0'; // ������ �ѱ� �� strlen ��ŭ�� �Ѱ�ٰ� ����
	printf(">> [���ŵ�����] %s\n", buf2);
	*/
}

void CMyClient::SendData(const char* msg, int length)
{
	// �۽�
	int	retval = send(Socket, msg, length, 0);
	printf("[�۽�] %d byte", length);

	// ����
	char buf[256];
	int retval2 = recv(Socket, buf, sizeof(buf), 0);
	if (retval2 == -1 || retval2 == 0)
	{
		// return  0 => ������ ����
		// return -1 => ������ �ı�, ���� ����
		printf("���� ���� or ������ ������\n");
		closesocket(Socket);
		return;
	}

	buf[retval2] = '\0';
	printf(">> [���ŵ�����] %s\n", buf);
}
