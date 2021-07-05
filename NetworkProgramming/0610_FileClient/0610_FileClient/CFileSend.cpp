// CFileSend.cpp
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "CFileSend.h"

#define FILE_BUFSIZE 4096

CFileSend::CFileSend(SOCKET _sock) // �ܺο��� ������ �޾� �帮�� ��.
{
	sock = _sock; 
}

bool CFileSend::FileSend(const char* filename)
{
	try
	{
		FILE* fp = fopen(filename,  // ���� �̸�
						 "rb");		// ��� ���� (�б�)

		if (fp == NULL)
		{
			throw "���� ���� ����";
		}

		FileNameSend(filename);
		int totalbytes = FileSizeSend(fp);
		FileDataSend(fp, totalbytes);

		return true;
	}
	catch (const char* msg)
	{
		printf("[����] %s", msg);
		return false;
	}
	
}

void CFileSend::FileNameSend(const char* filename)
{
	int retval = send(sock, filename, 100, 0);
	
	if (retval == SOCKET_ERROR)
	{
		throw "���� �̸� ���� ����";
	}
}

int CFileSend::FileSizeSend(FILE* fp)
{
	fseek(fp, 0, SEEK_END);		// ���������͸� ������ ������ �̵�
	int totalbytes = ftell(fp); // �ش� ������ġ ��ȯ

	// ���� ũ�� ������ (4byte)
	int retval = send(sock, (char*)&totalbytes, sizeof(totalbytes), 0);
	if (retval == SOCKET_ERROR)
	{
		throw "���� ũ�� ���� ����";
	}

	return totalbytes;
}

void CFileSend::FileDataSend(FILE* fp, int totalbytes)
{
	char buf[FILE_BUFSIZE];	//4096byte	
	int numread;
	int numtotal = 0;

	// ���� ������ ������
	rewind(fp); // ���� �����͸� ���� ������ �̵�
	// 1. �ó����� : buf�� ũ�Ⱑ 4096, ����ũ�� : 4096���� ���� �� �ִ�.
	// 				�ѹ��� read�� ������ ��ü ������ ȹ��
	// 				�� �� ��ȯ���� ���� ������ ũ��
	// 2. �ó����� : buf�� ũ�Ⱑ 4096, ����ũ�� : 4096���� Ŭ�� �ִ�.
	// 				�������� read�� ������ ��ü ������ ȹ��
	// 				��) 4096 + 4096 + 4096 + 10

	while (1) {
		numread = fread(buf, 1, FILE_BUFSIZE, fp); // 1 * BUFSIZE
		if (numread > 0) {
			int retval = send(sock, buf, numread, 0);
			if (retval == SOCKET_ERROR)
			{
				throw "���� ������ ���� ����";
				break;
			}
			numtotal += numread;
		}
		else if (numread == 0 && numtotal == totalbytes) 
		{
			// ���� ���� ���� ���� : numread == 0
			printf("���� ���� �Ϸ�!: %d ����Ʈ\n", numtotal);	
			break;
		}
		else 
		{
			throw "���� Read ����";
			break;
		}
	}
	fclose(fp);
	// closesocket()
	closesocket(sock);
	// ���� ����	
	WSACleanup();
}