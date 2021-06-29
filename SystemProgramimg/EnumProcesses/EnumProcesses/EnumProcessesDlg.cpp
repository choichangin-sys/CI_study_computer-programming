
// EnumProcessesDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "EnumProcesses.h"
#include "EnumProcessesDlg.h"
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


// CEnumProcessesDlg 대화 상자



CEnumProcessesDlg::CEnumProcessesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENUMPROCESSES_DIALOG, pParent)
	, m_KillName(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnumProcessesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlBox);
	DDX_Text(pDX, IDC_EDIT_KILLNAME, m_KillName);
}

BEGIN_MESSAGE_MAP(CEnumProcessesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEnumProcessesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_KILL, &CEnumProcessesDlg::OnBnClickedButtonKill)
	ON_BN_CLICKED(IDC_BUTTON3, &CEnumProcessesDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CEnumProcessesDlg 메시지 처리기

BOOL CEnumProcessesDlg::OnInitDialog()
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

void CEnumProcessesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEnumProcessesDlg::OnPaint()
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
HCURSOR CEnumProcessesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <Psapi.h>
#pragma comment(lib, "Psapi")
#include <winerror.h>

void CEnumProcessesDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD pidArray[512] = { 0, };
	DWORD cdNeeded;

	// 현재 실행중인 프로세스들의 ID를 모아준다.
	EnumProcesses(pidArray, sizeof(pidArray), &cdNeeded); // 핵심. 핸들의 ID를 모아서 돌려줌.

	int nProcesses = cdNeeded / sizeof(DWORD);

	for (int i = 0; i <= nProcesses; i++)
	{
		// for문을 통해서 Handle를 뽑아냄. 뭐로? Handle의 ID로(OpenProcess를 통해서).
		DWORD pid = pidArray[i];
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION 
									  | PROCESS_VM_READ,
									  FALSE, pid);

		if (hProcess != NULL)
		{
			TCHAR szbuffer[200];

			// 아래는 정보를 달라는 것.
			GetModuleFileNameEx(hProcess, NULL, szbuffer,
								sizeof(szbuffer));

			CString strTemp;
			strTemp.Format(_T("[PID:%d] %s"), pid, szbuffer);

			m_ctrlBox.AddString(strTemp);
		}
		else
		{
			CString strTemp;
			strTemp.Format(_T("[PID:%d] Error Code : %d"), pid, GetLastError());

	

			m_ctrlBox.AddString(strTemp);
		}
	}


}


void CEnumProcessesDlg::OnBnClickedButtonKill()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 1. Edit에서 글자 읽어오기
	UpdateData(1);

	// 2. 읽은 것으로 원하는 프로세스 죽이기
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,
								FALSE, m_KillName); // DWORD로 읽어야함.

	if (hProcess != NULL)
	{
		TerminateProcess(hProcess, -1);
		CloseHandle(hProcess);
	}

}

DWORD WINAPI WaitCall(LPVOID p)
{
	for (;;)
	{
		;// 전화가 오는지 검사한다.
	}
	return 0;
}

void CEnumProcessesDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	HANDLE hTh = CreateThread(NULL, 0, WaitCall, 0, 0, 0);
	CloseHandle(hTh);
}
