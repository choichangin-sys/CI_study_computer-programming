//control.h

#pragma once
#include "CMyClient.h"
//#include "FriendDemoDlg.h"

class CFriendDemoDlg;	//클래스 선언!(전방참조)

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
	CFriendDemoDlg* pForm = NULL;		//<============================

public:
	void RecvData(const char* msg, int size);
	void ParentForm(CFriendDemoDlg* pDlg);

public:
	void InsertMember(const char* msg, int age, char gender);
	void MemberList();
};

