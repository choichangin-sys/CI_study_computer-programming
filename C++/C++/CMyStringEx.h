#pragma once
#include"CMyString.h"

class CMyStringEx : public CMyString
{
public:
	CMyStringEx();
	CMyStringEx(const char* pszParam);
	~CMyStringEx();

	int GetLength() const;
	int Append(const char* pszParam) const;
	int Find(const char* pszParam);
};