//cmynet.cpp

#include <stdio.h>
#include <ws2tcpip.h>	//inet_pton
#include "CMyNet.h"

CMyNet* g_mynet = NULL;

CMyNet::CMyNet() : listen_socket(0)
{
	//1. ���̺귯�� �ʱ�ȭ(Winsock 2.2����)
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
	//2. ���̺귯�� ����
	WSACleanup();
}

void CMyNet::CreateSocket(int port)
{
	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_socket == INVALID_SOCKET)
		throw "���� ���� ����";

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));  //API ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // long���� network byte order��.
	int retval = bind(listen_socket, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
		throw "bind ����";

	retval = listen(listen_socket, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		throw "listen ����";

	Run();
}

void CMyNet::Run()
{
	SOCKET clientsocket;
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);  //<=======================�ʱ�ȭ
	
	printf("Ŭ���̾�Ʈ ���� ���:192.168.0.93:9000\n");

	while (true)
	{		
		clientsocket = accept(listen_socket, (SOCKADDR*)&clientaddr, &addrlen);
		if (clientsocket == INVALID_SOCKET)
		{
			printf("accept ����\n");
			continue;
		}

		char ip[20];
		int port;
		GetAddress(clientsocket, ip, &port);
		printf("[Ŭ���̾�Ʈ ����] %s:%d\n", ip, port);

		//vector�� ���� <------------------------------------------------
		clients.push_back(clientsocket); // 0��° �ε������� �������� ����
										 // �迭�� ũ�Ⱑ �ڵ����� ����!

		//��� ������ ����(������ ���� ����)
		CloseHandle(CreateThread(0, 0, WorkThread, (LPVOID)clientsocket, 0, 0));
		
	}
}

DWORD __stdcall CMyNet::WorkThread(LPVOID value)
{
	SOCKET sock = (SOCKET)value;	

	while (true)
	{
		//����
		char buf[256];
		int retval = recv(sock, buf, sizeof(buf), 0);
		if (retval == -1 || retval == 0)
		{
			printf("���� ���� or ������ ������\n");
			break;
		}

		buf[retval] = '\0'; //������ �ѱ涧 strlen()��ŭ�� �Ѱ�ٰ� ����!
		printf(">> [���ŵ�����] %s\n", buf);

		//��ü ����(1�� �� ���)
		for (int i = 0; i < (int)g_mynet->clients.size(); i++) //<====
		{
			SOCKET s = g_mynet->clients[i];	 //������ ������[]
			retval = send(s, buf, retval, 0);
		}		
		printf("[1�� �� �۽�] %dbyte\n", retval);
	}

	//vector ���� �˰���
	for (int i = 0; i < (int)g_mynet->clients.size(); i++) //<====
	{
		SOCKET s = g_mynet->clients[i];
		if (s == sock)
		{
			//erase�� ������ �迭�� �ּ�(��ġ)�� �䱸�Ѵ�.
			//- clients.begin() : �迭�� �����ּҸ� ��ȯ
			g_mynet->clients.erase( g_mynet->clients.begin() + i);
			closesocket(sock);
			return 0;
		}
	}
	return 0;
}

//����� ��� ������ �̿��ؼ� �ּҸ� ȹ��
//getpeername(����), getsockname(�ڽ�)
void CMyNet::GetAddress(SOCKET sock, char* ip, int* port)
{
	SOCKADDR_IN addr;
	int addrlenth= sizeof(addr);
	getpeername(sock, (SOCKADDR*)&addr, &addrlenth);
	
	//inet_ntoa : �����ּ� -> ���ڿ�
	//#include <ws2tcpip.h>	//inet_pton
	inet_ntop(AF_INET, &(addr.sin_addr.s_addr), ip, INET_ADDRSTRLEN);
	*port = ntohs(addr.sin_port);
}
