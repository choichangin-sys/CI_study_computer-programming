#include "CMyClient.h"
#include <WinSock2.h> // 선언부
#pragma comment(lib, "ws2_32.lib") // dll import정보
#include <stdio.h>
#include <ws2tcpip.h>
#include "Control.h"


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
	CloseHandle(CreateThread(0, 0, RecvMessageTread1, (LPVOID)this, 0, 0));
}

DWORD WINAPI CMyClient::RecvMessageTread1(LPVOID p)
{
	CMyClient* pClient = (CMyClient*)p; 
	SOCKET sock		   = (SOCKET)pClient->Socket;

	while (true)
	{
		// 수신
		char buf[48];
		int retval = pClient->Recvn(sock, buf, sizeof(buf), 0);
		if (retval == -1 || retval == 0)
		{
			// return  0 => 상대방이 종료
			// return -1 => 파이프 파괴, 소켓 오류
			printf("소켓 오류 or 상대방이 종료함\n");
			closesocket(sock);
			return 0;
		}

		
		printf(">> [수신데이터] %s\n", buf);

		Control::getInstance()->RecvData(buf, retval);
	}

	return 0;
}

void CMyClient::SendData(const char* msg, int length)
{
	// 송신
	int	retval = send(Socket, msg, length, 0);
	printf("[송신] %d byte\n", length);
}

int CMyClient::Recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;
	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}