// CServer.h

#pragma once

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>

class CServer
{
private:
	SOCKET listen_sock; // 대기소켓
	SOCKET sock;		// 통신소켓
	bool isConnect = FALSE;

public:
	CServer();
	~CServer();

public:
	SOCKET getSock() const;
	bool getIsConnect() const { return isConnect; }

public:
	bool CreateSocket(int port);
	void CloseSocket();

private:
	static DWORD WINAPI ListenThread(LPVOID p);
};

