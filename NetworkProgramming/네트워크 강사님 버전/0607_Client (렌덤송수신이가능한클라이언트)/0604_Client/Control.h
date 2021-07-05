//control.h

#pragma once
#include "CMyClient.h"

class Control
{
	//½Ì±ÛÅæ ÆÐÅÏ Àû¿ë ---------------------------------------------
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

public:
	void RecvData(const char* msg, int size);

public:
	void InsertMember();
	void Login();
};

