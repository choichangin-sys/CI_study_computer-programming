//control.h

#pragma once
#include "CMyClient.h"
//#include "FriendDemoDlg.h"

class CMy0608ClientDlg;	//Ŭ���� ����!(��������)

class Control
{
	//�̱��� ���� ���� ---------------------------------------------
private:
	Control();
	static Control* instance;
public:
	static Control* getInsatnce()
	{
		if (instance == NULL)
		{
			instance = new Control();
		}
		return instance;
	}
	//------------------------------------------------------------
	CMyClient client; 
	CMy0608ClientDlg* pForm = NULL; // <=====

public:
	void RecvData(const char* msg, int size);
	void ParentForm(CMy0608ClientDlg* pDlg); // <=====

	// Form -> Control ȣ���ϴ� �޼���
public:
	void InsertMember(const char* ID, const char* PW, const char* Name);
	void LoginMember(const char* ID, const char* PW);
};

