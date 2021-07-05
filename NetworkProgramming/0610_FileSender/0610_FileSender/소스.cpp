// 0610_FileSender
// [ Fule Sender ]
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

#define BUFSIZE 4096
#define FILE_NAME "�л����� �� DLL �ҽ�.txt"

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg);
// ���� �Լ� ���� ���
void err_display(const char* msg);

int main(int argc, char* argv[])
{
	int retval;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <FileName>\n", argv[0]);
		return -1;
	}

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");


	/*----------------------------- ���� IO ---------------------------------*/
	// ���� ����
	FILE* fp = fopen(argv[1], "rb");
	if (fp == NULL) { perror("���� ����� ����");		return -1; }

	// 1. ���� �̸� ������
	char filename[256];
	ZeroMemory(filename, 256);
	sprintf(filename, argv[1]);
	retval = send(sock, filename, 256, 0);
	if (retval == SOCKET_ERROR) err_quit("send()");

	// 2. ���� ũ�� ���
	fseek(fp, 0, SEEK_END); // ���������͸� ������ ������ �̵�
	int totalbytes = ftell(fp); // �ش� ������ġ ��ȯ

	// ���� ũ�� ������
	retval = send(sock, (char*)&totalbytes, sizeof(totalbytes), 0);
	if (retval == SOCKET_ERROR) err_quit("send()");



	// 3. ���� ������ ���ۿ� ����� ����
	char buf[BUFSIZE];	//4096byte	
	int numread;
	int numtotal = 0;

	// ���� ������ ������
	rewind(fp); // ���� �����͸� ���� ������ �̵�
	// 1. �ó����� : buf�� ũ�Ⱑ 4096, ����ũ�� : 4096���� ���� �� �ִ�.
	// 				�ѹ��� read�� ������ ��ü ������ ȹ��
	// 				 �� �� ��ȯ���� ���� ������ ũ��
	// 2. �ó����� : buf�� ũ�Ⱑ 4096, ����ũ�� : 4096���� Ŭ�� �ִ�.
	// 				�������� read�� ������ ��ü ������ ȹ��
	// 				��) 4096 + 4096 + 4096 + 10
	
	while (1) {
		numread = fread(buf, 1, BUFSIZE, fp); // 1 * BUFSIZE
		if (numread > 0) {
			retval = send(sock, buf, numread, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");				break;
			}
			numtotal += numread;
		}
		else if (numread == 0 && numtotal == totalbytes) {// ���� ���� ���� ���� : numread == 0
			printf("���� ���� �Ϸ�!: %d ����Ʈ\n", numtotal);			break;
		}
		else {
			perror("���� ����� ����");			break;
		}
	}
	fclose(fp);
	// closesocket()
	closesocket(sock);
	// ���� ����	
	WSACleanup();
	return 0;
}



// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}



// ���� �Լ� ���� ���
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
//=> Project -> Settign -> Debuf -> test.jpg
