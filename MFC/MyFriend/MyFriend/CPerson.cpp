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
	// ������ ������ �д� ������ ���ƾ��Ѵ�. (�ʼ�)

	if (ar.IsStoring())
	{	// storing code
		// ����
		ar << m_strName;
		ar << m_nAge;
		ar << m_bGender;
	}
	else
		// �б�
	{	// loading code
		ar >> m_strName;
		ar >> m_nAge;
		ar >> m_bGender;
	}
}
