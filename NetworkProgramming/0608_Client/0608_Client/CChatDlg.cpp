// CChatDlg.cpp: 구현 파일
//

#include "pch.h"
#include "0608_Client.h"
#include "CChatDlg.h"
#include "afxdialogex.h"

#include "0608_ClientDlg.h" // <=====


// CChatDlg 대화 상자

IMPLEMENT_DYNAMIC(CChatDlg, CDialogEx)

CChatDlg::CChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COMMUNICATION, pParent)
{

}

CChatDlg::~CChatDlg()
{
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatDlg 메시지 처리기
void CChatDlg::SendData(CString name)
{
	m_name = name;
}

BOOL CChatDlg::OnInitDialog()
{
	CString str;
	str.Format("%s님이 로그인하셨습니다.", m_name);
	SetWindowText(str);

	return true;
}