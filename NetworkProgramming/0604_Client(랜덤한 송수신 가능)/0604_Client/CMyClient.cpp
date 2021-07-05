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
	
	// ���� Thread �����ϴ� ��ġ
	CloseHandle(CreateThread(0, 0, RecvMessageTread1, (LPVOID)Socket, 0, 0));
}

DWORD WINAPI CMyClient::RecvMessageTread1(LPVOID p)
{
	SOCKET sock = (SOCKET)p;

	while (true)
	{
		// ����
		char buf[256];
		int retval2 = recv(sock, buf, sizeof(buf), 0);
		if (retval2 == -1 || retval2 == 0)
		{
			// return  0 => ������ ����
			// return -1 => ������ �ı�, ���� ����
			printf("���� ���� or ������ ������\n");
			closesocket(sock);
			return 0;
		}

		buf[retval2] = '\0';
		printf(">> [���ŵ�����] %s\n", buf);
	}

	return 0;
}

void CMyClient::SendData(const char* msg, int length)
{
	// �۽�
	int	retval = send(Socket, msg, length, 0);
	printf("[�۽�] %d byte", length);
}
