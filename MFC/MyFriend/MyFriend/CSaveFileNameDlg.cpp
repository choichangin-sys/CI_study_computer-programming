// CSaveFileNameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MyFriend.h"
#include "CSaveFileNameDlg.h"
#include "afxdialogex.h"


// CSaveFileNameDlg 대화 상자

IMPLEMENT_DYNAMIC(CSaveFileNameDlg, CDialogEx)

CSaveFileNameDlg::CSaveFileNameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAVENAMEFILE, pParent)
{

}

CSaveFileNameDlg::~CSaveFileNameDlg()
{
}

void CSaveFileNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveFileNameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVENAME, &CSaveFileNameDlg::OnBnClickedButtonSavename)
END_MESSAGE_MAP()


// CSaveFileNameDlg 메시지 처리기


void CSaveFileNameDlg::OnBnClickedButtonSavename()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}
