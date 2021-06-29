#include "pch.h"
#include "CPerson.h"

CPerson::CPerson()
{
	m_strName = _T("");
	m_nAge = 0;
	m_bGender = FALSE;
}

CPerson::~CPerson()
{

}

void CPerson::Serialize(CArchive& ar)
{
	// 저장한 순서와 읽는 순서가 같아야한다. (필수)

	if (ar.IsStoring())
	{	// storing code
		// 저장
		ar << m_strName;
		ar << m_nAge;
		ar << m_bGender;
	}
	else
		// 읽기
	{	// loading code
		ar >> m_strName;
		ar >> m_nAge;
		ar >> m_bGender;
	}
}
