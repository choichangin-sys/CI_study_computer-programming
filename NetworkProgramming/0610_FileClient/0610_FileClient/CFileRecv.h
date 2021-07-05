// CFileRecv.h

#pragma once

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>

class CFileRecv
{
private:
	SOCKET sock;

public:
	CFileRecv(SOCKET _sock);

public:
	bool FileRecv();

private:
	void FileNameRecv(char* filename);
	int	 FileSizeRecv();
	void FileDataRecv(const char* filename, int totalbytes);

	int	 recvn(SOCKET s, char* buf, int len, int flags);

	static DWORD WINAPI RecvThread(LPVOID p);
};

