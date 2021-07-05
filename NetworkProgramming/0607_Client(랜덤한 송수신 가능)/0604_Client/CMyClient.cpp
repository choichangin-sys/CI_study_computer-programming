#include "CMyClient.h"
#include <WinSock2.h> // �����
#pragma comment(lib, "ws2_32.lib") // dll import����
#include <stdio.h>
#include <ws2tcpip.h>
#include "Control.h"


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
	CloseHandle(CreateThread(0, 0, RecvMessageTread1, (LPVOID)this, 0, 0));
}

DWORD WINAPI CMyClient::RecvMessageTread1(LPVOID p)
{
	CMyClient* pClient = (CMyClient*)p; 
	SOCKET sock		   = (SOCKET)pClient->Socket;

	while (true)
	{
		// ����
		char buf[48];
		int retval = pClient->Recvn(sock, buf, sizeof(buf), 0);
		if (retval == -1 || retval == 0)
		{
			// return  0 => ������ ����
			// return -1 => ������ �ı�, ���� ����
			printf("���� ���� or ������ ������\n");
			closesocket(sock);
			return 0;
		}

		
		printf(">> [���ŵ�����] %s\n", buf);

		Control::getInstance()->RecvData(buf, retval);
	}

	return 0;
}

void CMyClient::SendData(const char* msg, int length)
{
	// �۽�
	int	retval = send(Socket, msg, length, 0);
	printf("[�۽�] %d byte\n", length);
}

int CMyClient::Recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;
	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}