#include <WinSock2.h> // 선언부
#pragma comment(lib, "ws2_32.lib") // dll import정보
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
	int Recvn(SOCKET s, char* buf, int len, int flags);

private:
	static DWORD WINAPI RecvMessageTread1(LPVOID p);
};

