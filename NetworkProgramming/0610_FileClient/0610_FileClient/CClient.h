// CClient.h

#pragma once

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>

class CClient
{
private:
	SOCKET sock;

public:
	CClient();
	~CClient();

public:
	SOCKET getSock() const;

public:
	bool CreateSocket(const char* ip, int port);
	void CloseSocket();
};

