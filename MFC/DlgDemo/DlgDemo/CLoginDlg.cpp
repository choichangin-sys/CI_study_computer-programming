// CLoginDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DlgDemo.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 대화 상자

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_strLoginEdit(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strLoginEdit);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DB, &CLoginDlg::OnBnClickedButtonDb)
END_MESSAGE_MAP()


// CLoginDlg 메시지 처리기


void CLoginDlg::OnBnClickedButtonDb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 1. 에디트 창의 글자를 읽어온다.
	UpdateData(1);

	// 2. 그 글자를 메시지 박스로 출력한다.
	AfxMessageBox(m_strLoginEdit);

	// 3. 정리
	UpdateData(0);

}
