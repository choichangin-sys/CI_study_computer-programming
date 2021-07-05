#pragma once
#include <vector>
#include <WinSock2.h> // �����
#pragma comment(lib, "ws2_32.lib") // dll import����

using namespace std;

class CMyNet
{
private:
	SOCKET listen_socket;
	vector<SOCKET> Client; // socket�� �����ϴ� �迭, ũ��� ���������� �����ȴ�.

	// ������ & �Ҹ���
public:
	CMyNet();
	~CMyNet();

	// �޼���
public:
	void CreateSocket(int port);

private:
	void Run();
	void GetAddress(SOCKET sock, char* ip, int* port);
	int Recvn(SOCKET s, char* buf, int len, int flags);

private:
	static DWORD WINAPI RecvMessageTread(LPVOID p);
};

