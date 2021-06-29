﻿
// CreateProssDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CreatePross.h"
#include "CreateProssDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCreateProssDlg 대화 상자



CCreateProssDlg::CCreateProssDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CREATEPROSS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateProssDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCreateProssDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATEPROSS, &CCreateProssDlg::OnBnClickedButtonCreatepross)
	ON_BN_CLICKED(IDC_BUTTON_WINEXC, &CCreateProssDlg::OnBnClickedButtonWinexc)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CCreateProssDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_TERMINATE, &CCreateProssDlg::OnBnClickedButtonTerminate)
END_MESSAGE_MAP()


// CCreateProssDlg 메시지 처리기

BOOL CCreateProssDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCreateProssDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCreateProssDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCreateProssDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCreateProssDlg::OnBnClickedButtonWinexc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	WinExec("Notepad.exe", SW_SHOWNORMAL); // WinExc를 사용한 방식

	/////////////////////////////////////////////////////////////
	// 노트패드와 통신하기

	CWnd* pWnd = FindWindow(_T("Notepad"), NULL);

	if (pWnd == NULL)
	{
		AfxMessageBox(_T("메모장을 찾을 수 없습니다."));
	}
	else
	{
		AfxMessageBox(_T("메모장을 찾았습니다."));
	}
}


void CCreateProssDlg::OnBnClickedButtonCreatepross()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR strPath[20] = _T("Notepad.exe");
	STARTUPINFO si = { sizeof(STARTUPINFO), };
	PROCESS_INFORMATION pi;

	::CreateProcess(NULL, strPath,
					NULL, NULL, // 보안속성이며 NULL이 기본이다.
					FALSE, 0, NULL, NULL,
					&si, &pi);

	//////////////////////////////////////////////////////////////
	WaitForInputIdle(pi.hProcess, INFINITE); 
	// 이것(pi.hProcess)이 만들어질 때까지 기다림.
	// 이 문구가 없으면 메모장을 못찾는다. 비동기이기 때문.
	// 이 문구가 있으므로 메모장을 찾게 된다. 확인하고 돌아옴.
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	CWnd* pWnd = FindWindow(_T("Notepad"), NULL);

	if (pWnd == NULL)
	{
		AfxMessageBox(_T("메모장을 찾을 수 없습니다."));
	}
	else
	{
		//AfxMessageBox(_T("메모장을 찾았습니다."));
		//Sleep(2000);
		TerminateProcess(GetCurrentProcess(), 0);
		// etCurrentProcess() 자기 자신의 핸들을 구하는 함수.
		pWnd->SendMessage(WM_CLOSE);
	}
}

void CCreateProssDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	ExitProcess(0);
	AfxMessageBox(_T("이 프로그램은 종료됩니다."));
}


void CCreateProssDlg::OnBnClickedButtonTerminate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR strPath[20] = _T("Notepad.exe");
	STARTUPINFO si = { sizeof(STARTUPINFO), };
	PROCESS_INFORMATION pi;

	::CreateProcess(NULL, strPath,
		NULL, NULL, // 보안속성이며 NULL이 기본이다.
		FALSE, 0, NULL, NULL,
		&si, &pi);
	///////////////////////////////////////////////////
	WaitForInputIdle(pi.hProcess, INFINITE);
	Sleep(1000);
	///////////////////////////////////////////////////

	TerminateProcess(pi.hProcess, 0);
	AfxMessageBox(_T("메모장은 종료됩니다."));
}
