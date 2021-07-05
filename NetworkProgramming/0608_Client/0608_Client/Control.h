//control.h

#pragma once
#include "CMyClient.h"
//#include "FriendDemoDlg.h"

class CMy0608ClientDlg;	//클래스 선언!(전방참조)

class Control
{
	//싱글톤 패턴 적용 ---------------------------------------------
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

	// Form -> Control 호출하는 메서드
public:
	void InsertMember(const char* ID, const char* PW, const char* Name);
	void LoginMember(const char* ID, const char* PW);
};

