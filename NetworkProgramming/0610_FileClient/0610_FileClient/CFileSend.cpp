// CFileSend.cpp
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "CFileSend.h"

#define FILE_BUFSIZE 4096

CFileSend::CFileSend(SOCKET _sock) // 외부에서 소켓을 받아 드리는 것.
{
	sock = _sock; 
}

bool CFileSend::FileSend(const char* filename)
{
	try
	{
		FILE* fp = fopen(filename,  // 파일 이름
						 "rb");		// 사용 형식 (읽기)

		if (fp == NULL)
		{
			throw "파일 생성 오류";
		}

		FileNameSend(filename);
		int totalbytes = FileSizeSend(fp);
		FileDataSend(fp, totalbytes);

		return true;
	}
	catch (const char* msg)
	{
		printf("[에러] %s", msg);
		return false;
	}
	
}

void CFileSend::FileNameSend(const char* filename)
{
	int retval = send(sock, filename, 100, 0);
	
	if (retval == SOCKET_ERROR)
	{
		throw "파일 이름 전송 오류";
	}
}

int CFileSend::FileSizeSend(FILE* fp)
{
	fseek(fp, 0, SEEK_END);		// 파일포인터를 파일의 끝으로 이동
	int totalbytes = ftell(fp); // 해당 파일위치 반환

	// 파일 크기 보내기 (4byte)
	int retval = send(sock, (char*)&totalbytes, sizeof(totalbytes), 0);
	if (retval == SOCKET_ERROR)
	{
		throw "파일 크기 전송 오류";
	}

	return totalbytes;
}

void CFileSend::FileDataSend(FILE* fp, int totalbytes)
{
	char buf[FILE_BUFSIZE];	//4096byte	
	int numread;
	int numtotal = 0;

	// 파일 데이터 보내기
	rewind(fp); // 파일 포인터를 제일 앞으로 이동
	// 1. 시나리오 : buf의 크기가 4096, 파일크기 : 4096보다 작을 수 있다.
	// 				한번의 read로 파일의 전체 데이터 획득
	// 				이 때 반환값은 실제 파일의 크기
	// 2. 시나리오 : buf의 크기가 4096, 파일크기 : 4096보다 클수 있다.
	// 				여러번의 read로 파일의 전체 데이터 획득
	// 				예) 4096 + 4096 + 4096 + 10

	while (1) {
		numread = fread(buf, 1, FILE_BUFSIZE, fp); // 1 * BUFSIZE
		if (numread > 0) {
			int retval = send(sock, buf, numread, 0);
			if (retval == SOCKET_ERROR)
			{
				throw "파일 데이터 전송 오류";
				break;
			}
			numtotal += numread;
		}
		else if (numread == 0 && numtotal == totalbytes) 
		{
			// 읽을 것이 없는 상태 : numread == 0
			printf("파일 전송 완료!: %d 바이트\n", numtotal);	
			break;
		}
		else 
		{
			throw "파일 Read 오류";
			break;
		}
	}
	fclose(fp);
	// closesocket()
	closesocket(sock);
	// 윈속 종료	
	WSACleanup();
}