#include <WinSock2.h> // �����
#pragma comment(lib, "ws2_32.lib") // dll import����
#include <stdio.h>
#include <ws2tcpip.h>

#pragma once
class CMyClient
{
private:
	SOCKET Socket;

public:
	CMyClient();
	~CMyClient();

public:
	void CreateSocket(const char* ip, int port);
	void SendData(const char* msg, int length);
};

