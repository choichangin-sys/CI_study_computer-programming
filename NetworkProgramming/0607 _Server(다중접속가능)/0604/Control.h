// Control.h
/*
	����������(Gof) : � ������ �ذ��ϱ� ���� Ŭ������ ��� ������ ���ΰ�?
					 �𵨿� ���� �̾߱�.

	��) �̱�������
		�ϳ��� ��ü�� ���������� Ŭ���� ����.
*/
#pragma once
#include <stdio.h>
#include <vector>
#include "Packet.h"

using namespace std;

class Control
{

// �̱��� ���� ���� ------------------------------------------------------
private:
	Control() { }
	static Control* instance;

public:
	static Control* getInstance() 
	{ 
		if (instance == NULL)
		{
			instance = new Control();
		}
		return instance;
	}
// ---------------------------------------------------------------------

private:
	vector<NEWMEMBER> memberlist;

public:
	void RecvData(const char* msg, int size);
	// ����Լ�...

private:
	bool NewMember(NEWMEMBER* pMem);
	bool Login(LOGIN* pLogin);
	void PrintMemberData();
};

