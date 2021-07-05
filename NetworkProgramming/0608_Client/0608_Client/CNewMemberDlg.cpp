// CNewMemberDlg.cpp: 구현 파일
//

#include "pch.h"
#include "0608_Client.h"
#include "CNewMemberDlg.h"
#include "afxdialogex.h"


// CNewMemberDlg 대화 상자

IMPLEMENT_DYNAMIC(CNewMemberDlg, CDialogEx)

CNewMemberDlg::CNewMemberDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Join, pParent)
	, m_strID(_T(""))
	, m_strPassword(_T(""))
	, m_strName(_T(""))
{

}

CNewMemberDlg::~CNewMemberDlg()
{
}

void CNewMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strID);
	DDX_Text(pDX, IDC_EDIT2, m_strPassword);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
}


BEGIN_MESSAGE_MAP(CNewMemberDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RealJoin, &CNewMemberDlg::OnBnClickedButtonRealjoin)
	ON_BN_CLICKED(IDC_BUTTON_Check, &CNewMemberDlg::OnBnClickedButtonCheck)
END_MESSAGE_MAP()


// CNewMemberDlg 메시지 처리기

// 중복체크
void CNewMemberDlg::OnBnClickedButtonCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);
	m_strID;

	// 서버로 전송
}

// 회원가입
void CNewMemberDlg::OnBnClickedButtonRealjoin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// UpdateData(1);
	// IDOK 반환 설정.
	CNewMemberDlg::OnOK(); // 위 두 기능을 얘가 대신 함.
}

// 회원가입을 할 시 입력받은 정보를 받아옴.
void CNewMemberDlg::GetData(CString& ID, CString& PW, CString& Name)
{
	// TODO: 여기에 구현 코드 추가.
	ID = m_strID;
	PW = m_strPassword;
	Name = m_strName;
}
