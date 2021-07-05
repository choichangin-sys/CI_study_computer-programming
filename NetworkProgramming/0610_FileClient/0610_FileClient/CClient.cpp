// CClient.cpp

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "CClient.h"

CClient::CClient() : sock(0)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		exit(-1);
	}
}

CClient::~CClient() 
{
	WSACleanup();
}

SOCKET CClient::getSock() const
{
	return sock;
}

bool CClient::CreateSocket(const char* ip, int port)
{
	// socket()
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		printf("에러 발생[1]");
		return false;
	}

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = inet_addr(ip);
	int retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		printf("Client 에러 발생");
		return false;
	}
	else
	{
		return true;
	}
}

void CClient::CloseSocket()
{
	closesocket(sock);
}