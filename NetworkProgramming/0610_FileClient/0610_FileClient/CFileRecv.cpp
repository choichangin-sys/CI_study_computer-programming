// CFileRecv.cpp

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "CFileRecv.h"

#define FILE_BUFSIZE 4096

CFileRecv::CFileRecv(SOCKET _sock) // �ܺο��� ������ �޾� �帮�� ��.
{
	sock = _sock;
}

bool CFileRecv::FileRecv()
{
	CloseHandle(CreateThread(0, 0, RecvThread, this, 0, 0));

	return true;
}

DWORD WINAPI CFileRecv::RecvThread(LPVOID p)
{
	CFileRecv* pThis= (CFileRecv*)p;
	try
	{
		char filename[100];
		ZeroMemory(filename, 100);
		pThis->FileNameRecv(filename);
		int totalbytes = pThis->FileSizeRecv();
		pThis->FileDataRecv(filename, totalbytes);
		return 1;
	}
	catch (const char* msg)
	{
		printf("[����] %s\n", msg);
		return 0;
	}
}

void CFileRecv::FileNameRecv(char* filename)
{
	int retval = recvn(sock, filename, 100, 0);
	if (retval == SOCKET_ERROR) 
	{
		throw "���ϸ� ���� ����";
	}

	printf("-> ���� ���� �̸�: %s\n", filename);
}

int	 CFileRecv::FileSizeRecv()
{
	int totalbytes;
	int retval = recvn(sock, (char*)&totalbytes, sizeof(totalbytes), 0);
	if (retval == SOCKET_ERROR)
	{
		throw "���� ũ�� ���� ����";
	}
	printf("-> ���� ���� ũ��: %d\n", totalbytes);

	return totalbytes;
}

void CFileRecv::FileDataRecv(const char* filename, int totalbytes)
{
	// ���� ����
	FILE* fp = fopen(filename, "wb");
	if (fp == NULL)
	{
		throw "���� ���� ����";
	}

	// ���� ������ �ޱ�
	char buf[FILE_BUFSIZE];
	int numtotal = 0;
	while (true)
	{
		int retval = recvn(sock, buf, FILE_BUFSIZE, 0);
		if (retval == SOCKET_ERROR) 
		{
			throw "���� ������ ���� ����";
			break;
		}
		else if (retval == 0)
		{
			break;
		}
		else 
		{
			fwrite(buf, 1, retval, fp);
			if (ferror(fp))
			{
				throw "���� ������ ���� ����";
				break;
			}

			numtotal += retval;
		}
	}
	fclose(fp);

	if (numtotal != totalbytes)
	{
		throw "���� ���� ����";
	}
}

int CFileRecv::recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;

	int left = len;

	while (left > 0) {
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