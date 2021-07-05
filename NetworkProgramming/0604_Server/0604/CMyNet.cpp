#include "CMyNet.h"
#include <WinSock2.h> // �����
#pragma comment(lib, "ws2_32.lib") // dll import����
#include <stdio.h>
#include <ws2tcpip.h>

CMyNet::CMyNet()
{
	// 1. ���̺귯�� �ʱ�ȭ(winsock 2.2����)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		exit(-1);
	}
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

		RecvWorkMessage(ClientSocket);
	}
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

// echo(�޾Ƹ�)
void CMyNet::RecvWorkMessage(SOCKET sock)
{
	while (true)
	{
		// ����
		char buf[256];
		// sock�� ����� �������κ��� ���޵� �޽����� �����ϰڴ�.
		// ��, ������ ���� sizeof(buf)�� ũ�⸦ �غ��߰�, �� ������ ������ġ�� ����.
		// ������ ���� ���� ���ŵ� byte ũ�⸦ Ȯ���� �� �ִ�.
		int retval = recv(sock, buf, sizeof(buf), 0);
		if (retval == -1 || retval == 0)
		{
			printf("���� ���� or ������ ������\n");
			break;
		}

		buf[retval] = '\0'; // ������ �ѱ� �� strlen ��ŭ�� �Ѱ�ٰ� ����
		printf(">> [���ŵ�����] %s\n", buf);

		// ���ŵ� ������ �״�� �۽�
		// buf�� �ּҷκ��� retval�� byte��ŭ �����ض�
		retval = send(sock, buf, retval, 0);
		printf("[�۽�] %d byte", retval);
	}

	closesocket(listen_socket);
}