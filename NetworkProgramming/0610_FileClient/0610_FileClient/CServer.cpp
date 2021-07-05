#include "CServer.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

CServer::CServer() : sock(0), listen_sock(0)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		exit(-1);
	}
}

CServer::~CServer()
{
	WSACleanup();
}

SOCKET CServer::getSock() const
{
	return sock;
}

bool CServer::CreateSocket(int port)
{
	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
	{
		printf("에러 발생[1]");
		return false;
	}

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		printf("에러 발생[2]");
		return false;
	}

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		printf("에러 발생[3]");
		return false;
	}

	// accept()
	CloseHandle(CreateThread(0, 0, ListenThread, this, 0, 0));
	
	return true;
}

DWORD WINAPI CServer::ListenThread(LPVOID p)
{
	HANDLE hEvebt;
	hEvebt = CreateEvent(0, FALSE, FALSE, "e"); // 두 번 불리면 오픈으로 시작됨.

	CServer* pserver = (CServer*)p;
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	pserver->sock = accept(pserver->listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
	if (pserver->sock == INVALID_SOCKET)
	{
		exit(-1);
	}
	

	SetEvent(hEvebt);
	pserver->isConnect = TRUE;
	CloseHandle(hEvebt);

	return -1;
}

void CServer::CloseSocket()
{
	closesocket(sock);
	closesocket(listen_sock);
}