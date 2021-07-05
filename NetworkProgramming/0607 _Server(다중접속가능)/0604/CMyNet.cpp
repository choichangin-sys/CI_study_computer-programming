#include "CMyNet.h"
#include <WinSock2.h> // 선언부
#pragma comment(lib, "ws2_32.lib") // dll import정보
#include <stdio.h>
#include <ws2tcpip.h>
#include "Control.h"

// 이것을 없애고 싶다면 구조체를 정의
// 구조체 정의 (멤버 : CMyNet*, SOCKET)
// CreateThread할 때 구조체 변수의 주소를 전달
CMyNet* g_mynet = NULL; // 자기 자신의 객체에 접근할 수 있는 글로벌 변수

CMyNet::CMyNet()
{
	// 1. 라이브러리 초기화(winsock 2.2버전)
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("원도우 소켓 초기화 실패\n");
		exit(-1);
	}
	g_mynet = this;
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

		// vector에 저장
		Client.push_back(ClientSocket); // 0번째 인덱스부터 차곡차곡 저장
										// 배열의 크기가 자동으로 증가

		// 통신 스레드 생성(접속한 소켓 전달)
		CloseHandle(CreateThread(0, 0, RecvMessageTread, (LPVOID)ClientSocket, 0, 0));
	}

}

DWORD WINAPI CMyNet::RecvMessageTread(LPVOID p)
{
	SOCKET sock = (SOCKET)p;
	
	while (true)
	{
		// 수신
		char buf[48]; // 한글 3자, 영문 6자
		int retval = g_mynet->Recvn(sock, buf, sizeof(buf) - 1, 0); // \0을 제외한 나머지
		
		if (retval == -1 || retval == 0)
		{
			printf("소켓 오류 or 상대방이 종료함\n");
			break;
		}

		buf[retval] = '\0'; // 상대방이 넘길 떄 strlen 만큼만 넘겼다고 가정
		printf(">> [수신데이터] %dbyte\n", retval);

		Control::getInstance()->RecvData(buf, retval);

		// 개인에게 전달
		retval = send(sock, buf, retval, 0);
		printf("[1대 1 송신] %d byte", retval);

		//// 전체 전송 (1대 다 통신)
		////g_mynet->Client;
		//for (int i = 0; i < (int)g_mynet->Client.size(); i++)
		//{
		//	SOCKET s = g_mynet->Client[i];
		//	// 수신된 정보를 그대로 송신
		//	// buf의 주소로부터 retval의 byte만큼 전송해라
		//	retval = send(s, buf, retval, 0);
		//}
		////printf("[1대 다 송신] %d byte", retval);
	}

	// vertor 삭제 알고리즘
	for (int i = 0; (int)g_mynet->Client.size(); i++)
	{
		SOCKET s = g_mynet->Client[i];
		if (s == sock)
		{
			// erase는 삭제할 배열의 주소(위치)를 요구한다
			// Client.begin() : 배열의 시작주소를 반환
			g_mynet->Client.erase(g_mynet->Client.begin() + i);
			closesocket(sock);
			return 0;
		}
	}

	return 0;
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

/*
[recv --> Recvn]
1. Recvn을 클래스의 멤버함수로 정의.

2. WorkThread의 recv함수를 Recvn함수로 변경처리.
*/

int CMyNet::Recvn(SOCKET s, char* buf, int len, int flags)
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