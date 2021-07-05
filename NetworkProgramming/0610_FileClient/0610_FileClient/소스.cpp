// 0610_FileClient

#include <stdio.h>
#include <conio.h>
#include "CServer.h"
#include "CClient.h"
#include "CFileSend.h"
#include "CFileRecv.h"

#define IP "127.0.0.1"
#define PORT 9000
#define FILE "C:\Users\pc\source\repos\NetworkProgramming\0610_FileClient\TestFile.txt"
int main()
{
	HANDLE hEvebt;
	hEvebt = CreateEvent(0, FALSE, FALSE, "e"); // 자동, nonsignal

	printf("---------------------\n");
	printf("[1] Server [2] Client\n");
	printf("---------------------\n");
	char idx = _getch();

	if (idx == '1')
	{
		// 무식한 방법
		/*
		CServer server;
		server.CreateSocket(PORT);
		while (true)
		{
			if (server.getIsConnect() == true) // 이벤트 사용
			{
				CFileSend send(server.getSock());
				break;
			}
		}
		*/
		// 선호하는 방식
		CServer server;
		server.CreateSocket(PORT);
		printf("클라이언트 대기\n");
		WaitForSingleObject(hEvebt, INFINITE);
		printf("클라이언트 접속\n");
		CFileSend send(server.getSock());
	}
	else if (idx == '2')
	{
		CClient client; // 수신
		client.CreateSocket(IP, PORT);
		CFileRecv recv(client.getSock());
	}

	CloseHandle(hEvebt);

	return 0;
}