#include "CMyClient.h"
#include <WinSock2.h> // 선언부
#pragma comment(lib, "ws2_32.lib") // dll import정보
#include <stdio.h>
#include <ws2tcpip.h>

CMyClient::CMyClient()
{
	// 1. 라이브러리 초기화(winsock 2.2버전)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("원도우 소켓 초기화 실패\n");
		exit(-1);
	}
}

CMyClient::~CMyClient()
{
	// 2. 라이브러리 해제
	WSACleanup();
}

void CMyClient::CreateSocket(const char* ip, int port)
{
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		throw "소켓 생성 오류";
	}

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	unsigned int numberaddr;
	inet_pton(AF_INET, ip, &numberaddr);
	addr.sin_addr.s_addr = numberaddr;
	int retval = connect(Socket, (SOCKADDR*)&addr, sizeof(addr));

	if (retval == SOCKET_ERROR)
	{
		throw "서버 연결 오류";
	}
	
	// 수신 Thread 생성하는 위치
	CloseHandle(CreateThread(0, 0, RecvMessageTread1, (LPVOID)Socket, 0, 0));
}

DWORD WINAPI CMyClient::RecvMessageTread1(LPVOID p)
{
	SOCKET sock = (SOCKET)p;

	while (true)
	{
		// 수신
		char buf[256];
		int retval2 = recv(sock, buf, sizeof(buf), 0);
		if (retval2 == -1 || retval2 == 0)
		{
			// return  0 => 상대방이 종료
			// return -1 => 파이프 파괴, 소켓 오류
			printf("소켓 오류 or 상대방이 종료함\n");
			closesocket(sock);
			return 0;
		}

		buf[retval2] = '\0';
		printf(">> [수신데이터] %s\n", buf);
	}

	return 0;
}

void CMyClient::SendData(const char* msg, int length)
{
	// 송신
	int	retval = send(Socket, msg, length, 0);
	printf("[송신] %d byte", length);
}
