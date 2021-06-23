#define _CRT_SECURE_NO_WARNINGS
#include"CMyStringEx.h"
#include<string.h>
#include<iostream>
using namespace std;

CMyStringEx::CMyStringEx() {};
CMyStringEx::CMyStringEx(const char* pszParam) 
: CMyString::CMyString(pszParam)
{

	/*this->m_nLength = strlen(pszParam);
	this->m_pszData = new char[m_nLength + 1];
	strcpy(this->m_pszData, pszParam);*/
};
CMyStringEx::~CMyStringEx() {
};



int CMyStringEx::GetLength() const { return m_nLength; };

int CMyStringEx::Append(const char* pszParam) const
{
	 
	char* szTemp = new char[strlen(pszParam) + GetLength() + 1];
	strcpy(szTemp,"\0");
	strcat(szTemp, this->m_pszData);
	strcat(szTemp, pszParam);
	strcpy(this->m_pszData, szTemp);

	delete[] szTemp;
	return 0;

};

int CMyStringEx::Find(const char* pszParam) 
{ 
	char* ptr = strstr(this->m_pszData, pszParam);
	if(ptr!=NULL)
		return 1;
	else
		return 0;
	
};
