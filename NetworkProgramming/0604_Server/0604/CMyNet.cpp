#include "CMyNet.h"
#include <WinSock2.h> // 선언부
#pragma comment(lib, "ws2_32.lib") // dll import정보
#include <stdio.h>
#include <ws2tcpip.h>

CMyNet::CMyNet()
{
	// 1. 라이브러리 초기화(winsock 2.2버전)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("원도우 소켓 초기화 실패\n");
		exit(-1);
	}
}

CMyNet::~CMyNet()
{
	// 2. 라이브러리 해제
	WSACleanup();
}

void CMyNet::CreateSocket(int port)
{
	// Soket() -> bind() -> listen()
	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listen_socket == INVALID_SOCKET)
	{
		throw "소켓 생성 오류";
	}
	
	SOCKADDR_IN Addr;
	memset(&Addr, 0, sizeof(Addr)); // 초기화
	// API ZeroMemory(&Addr, sizeof(Addr)), 위와 같은 의미
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(port);
	Addr.sin_addr.s_addr = htonl(INADDR_ANY); // long형을 Network Byte Order로.

	int retval = bind(listen_socket, (SOCKADDR*)&Addr, sizeof(Addr));
	
	if (retval == SOCKET_ERROR)
	{
		throw "bind 오류";
	}

	retval = listen(listen_socket, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		throw "listen 오류";
	}

	Run();
}

void CMyNet::Run()
{
	// accept
	SOCKET ClientSocket;
	SOCKADDR_IN  ClientAddr;
	int Addrlen = sizeof(ClientAddr); // 초기화
	// int Addrlen; // 초기화를 안하면 accept가 정상작동을 못함.

	while (true)
	{
		printf("클라이언트 연결 대기\n");
		ClientSocket = accept(listen_socket, (SOCKADDR*)&ClientAddr, &Addrlen);
	
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept 오류\n");
			continue;
		}

		char ip[20];
		int port;
		GetAddress(ClientSocket, ip, &port);
		printf("[클라이언트 접속] %s:%d", ip, port);

		RecvWorkMessage(ClientSocket);
	}
}

// 연결된 통신 소켓을 이용해서 주소를 획득할 수 있다.
// 주소는 내 주소와 상대방 주소가 있어서 함수는 2개가 있다.
// getpeername(상대방), getsockname(자신)
void CMyNet::GetAddress(SOCKET sock, char* ip, int* port)
{
	SOCKADDR_IN Addr;
	int addrlenth = sizeof(Addr);
	getpeername(sock, (SOCKADDR*)&Addr, &addrlenth);
	
	// inet_ntoa : 정수주소 -> 문자열
	// 아래는 자주 사용되므로 잘 알아둘 것.
	inet_ntop(AF_INET, &(Addr.sin_addr.s_addr), ip, INET_ADDRSTRLEN);
	*port = ntohs(Addr.sin_port);
}

// echo(메아리)
void CMyNet::RecvWorkMessage(SOCKET sock)
{
	while (true)
	{
		// 수신
		char buf[256];
		// sock에 연결된 상대방으로부터 전달된 메시지를 수신하겠다.
		// 단, 수신을 위해 sizeof(buf)의 크기를 준비했고, 그 버퍼의 시작위치를 전달.
		// 리턴을 통해 실제 수신된 byte 크기를 확인할 수 있다.
		int retval = recv(sock, buf, sizeof(buf), 0);
		if (retval == -1 || retval == 0)
		{
			printf("소켓 오류 or 상대방이 종료함\n");
			break;
		}

		buf[retval] = '\0'; // 상대방이 넘길 떄 strlen 만큼만 넘겼다고 가정
		printf(">> [수신데이터] %s\n", buf);

		// 수신된 정보를 그대로 송신
		// buf의 주소로부터 retval의 byte만큼 전송해라
		retval = send(sock, buf, retval, 0);
		printf("[송신] %d byte", retval);
	}

	closesocket(listen_socket);
}