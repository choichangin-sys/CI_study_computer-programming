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

	/*
	char buf1[20] = "최창인~";
	retval = send(Socket, buf1, strlen(buf1), 0);

	// 수신
	char buf2[20];
	// sock에 연결된 상대방으로부터 전달된 메시지를 수신하겠다.
	// 단, 수신을 위해 sizeof(buf)의 크기를 준비했고, 그 버퍼의 시작위치를 전달.
	// 리턴을 통해 실제 수신된 byte 크기를 확인할 수 있다.
	int retval2 = recv(Socket, buf2, sizeof(buf2), 0);
	if (retval2 == -1 || retval2 == 0)
	{
		printf("소켓 오류 or 상대방이 종료함\n");
		return;
	}

	buf2[retval2] = '\0'; // 상대방이 넘길 떄 strlen 만큼만 넘겼다고 가정
	printf(">> [수신데이터] %s\n", buf2);
	*/
}

void CMyClient::SendData(const char* msg, int length)
{
	// 송신
	int	retval = send(Socket, msg, length, 0);
	printf("[송신] %d byte", length);

	// 수신
	char buf[256];
	int retval2 = recv(Socket, buf, sizeof(buf), 0);
	if (retval2 == -1 || retval2 == 0)
	{
		// return  0 => 상대방이 종료
		// return -1 => 파이프 파괴, 소켓 오류
		printf("소켓 오류 or 상대방이 종료함\n");
		closesocket(Socket);
		return;
	}

	buf[retval2] = '\0';
	printf(">> [수신데이터] %s\n", buf);
}
