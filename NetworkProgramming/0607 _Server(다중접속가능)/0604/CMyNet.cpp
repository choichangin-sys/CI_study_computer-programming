#include "CMyNet.h"
#include <WinSock2.h> // �����
#pragma comment(lib, "ws2_32.lib") // dll import����
#include <stdio.h>
#include <ws2tcpip.h>
#include "Control.h"

// �̰��� ���ְ� �ʹٸ� ����ü�� ����
// ����ü ���� (��� : CMyNet*, SOCKET)
// CreateThread�� �� ����ü ������ �ּҸ� ����
CMyNet* g_mynet = NULL; // �ڱ� �ڽ��� ��ü�� ������ �� �ִ� �۷ι� ����

CMyNet::CMyNet()
{
	// 1. ���̺귯�� �ʱ�ȭ(winsock 2.2����)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		exit(-1);
	}
	g_mynet = this;
}

CMyNet::~CMyNet()
{
	// 2. ���̺귯�� ����
	WSACleanup();
}

void CMyNet::CreateSocket(int port)
{
	// Soket() -> bind() -> listen()
	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listen_socket == INVALID_SOCKET)
	{
		throw "���� ���� ����";
	}
	
	SOCKADDR_IN Addr;
	memset(&Addr, 0, sizeof(Addr)); // �ʱ�ȭ
	// API ZeroMemory(&Addr, sizeof(Addr)), ���� ���� �ǹ�
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(port);
	Addr.sin_addr.s_addr = htonl(INADDR_ANY); // long���� Network Byte Order��.

	int retval = bind(listen_socket, (SOCKADDR*)&Addr, sizeof(Addr));
	
	if (retval == SOCKET_ERROR)
	{
		throw "bind ����";
	}

	retval = listen(listen_socket, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		throw "listen ����";
	}

	Run();
}

void CMyNet::Run()
{
	// accept
	SOCKET ClientSocket;
	SOCKADDR_IN  ClientAddr;
	int Addrlen = sizeof(ClientAddr); // �ʱ�ȭ
	// int Addrlen; // �ʱ�ȭ�� ���ϸ� accept�� �����۵��� ����.

	while (true)
	{
		printf("Ŭ���̾�Ʈ ���� ���\n");
		ClientSocket = accept(listen_socket, (SOCKADDR*)&ClientAddr, &Addrlen);
	
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept ����\n");
			continue;
		}

		char ip[20];
		int port;
		GetAddress(ClientSocket, ip, &port);
		printf("[Ŭ���̾�Ʈ ����] %s:%d", ip, port);

		// vector�� ����
		Client.push_back(ClientSocket); // 0��° �ε������� �������� ����
										// �迭�� ũ�Ⱑ �ڵ����� ����

		// ��� ������ ����(������ ���� ����)
		CloseHandle(CreateThread(0, 0, RecvMessageTread, (LPVOID)ClientSocket, 0, 0));
	}

}

DWORD WINAPI CMyNet::RecvMessageTread(LPVOID p)
{
	SOCKET sock = (SOCKET)p;
	
	while (true)
	{
		// ����
		char buf[48]; // �ѱ� 3��, ���� 6��
		int retval = g_mynet->Recvn(sock, buf, sizeof(buf) - 1, 0); // \0�� ������ ������
		
		if (retval == -1 || retval == 0)
		{
			printf("���� ���� or ������ ������\n");
			break;
		}

		buf[retval] = '\0'; // ������ �ѱ� �� strlen ��ŭ�� �Ѱ�ٰ� ����
		printf(">> [���ŵ�����] %dbyte\n", retval);

		Control::getInstance()->RecvData(buf, retval);

		// ���ο��� ����
		retval = send(sock, buf, retval, 0);
		printf("[1�� 1 �۽�] %d byte", retval);

		//// ��ü ���� (1�� �� ���)
		////g_mynet->Client;
		//for (int i = 0; i < (int)g_mynet->Client.size(); i++)
		//{
		//	SOCKET s = g_mynet->Client[i];
		//	// ���ŵ� ������ �״�� �۽�
		//	// buf�� �ּҷκ��� retval�� byte��ŭ �����ض�
		//	retval = send(s, buf, retval, 0);
		//}
		////printf("[1�� �� �۽�] %d byte", retval);
	}

	// vertor ���� �˰���
	for (int i = 0; (int)g_mynet->Client.size(); i++)
	{
		SOCKET s = g_mynet->Client[i];
		if (s == sock)
		{
			// erase�� ������ �迭�� �ּ�(��ġ)�� �䱸�Ѵ�
			// Client.begin() : �迭�� �����ּҸ� ��ȯ
			g_mynet->Client.erase(g_mynet->Client.begin() + i);
			closesocket(sock);
			return 0;
		}
	}

	return 0;
}

// ����� ��� ������ �̿��ؼ� �ּҸ� ȹ���� �� �ִ�.
// �ּҴ� �� �ּҿ� ���� �ּҰ� �־ �Լ��� 2���� �ִ�.
// getpeername(����), getsockname(�ڽ�)
void CMyNet::GetAddress(SOCKET sock, char* ip, int* port)
{
	SOCKADDR_IN Addr;
	int addrlenth = sizeof(Addr);
	getpeername(sock, (SOCKADDR*)&Addr, &addrlenth);
	
	// inet_ntoa : �����ּ� -> ���ڿ�
	// �Ʒ��� ���� ���ǹǷ� �� �˾Ƶ� ��.
	inet_ntop(AF_INET, &(Addr.sin_addr.s_addr), ip, INET_ADDRSTRLEN);
	*port = ntohs(Addr.sin_port);
}

/*
[recv --> Recvn]
1. Recvn�� Ŭ������ ����Լ��� ����.

2. WorkThread�� recv�Լ��� Recvn�Լ��� ����ó��.
*/

int CMyNet::Recvn(SOCKET s, char* buf, int len, int flags)
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