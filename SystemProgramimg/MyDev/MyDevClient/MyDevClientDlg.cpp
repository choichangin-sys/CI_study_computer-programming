
// MyDevClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MyDevClient.h"
#include "MyDevClientDlg.h"
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


// CMyDevClientDlg 대화 상자



CMyDevClientDlg::CMyDevClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYDEVCLIENT_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDevClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CMyDevClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDevClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDevClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyDevClientDlg::OnBnClickedButton3)

END_MESSAGE_MAP()


// CMyDevClientDlg 메시지 처리기

BOOL CMyDevClientDlg::OnInitDialog()
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

void CMyDevClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyDevClientDlg::OnPaint()
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
HCURSOR CMyDevClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 암시적 연결 ///////////////////////////
// 실행시작시 : 암시적 연결
// dll이 없으면 안켜짐.
#include "MyDev.h"
#pragma comment(lib, "MyDev.lib")
////////////////////////////////////////

typedef struct USERDATA
{
	int x;
	int y;
} USERDATA;

int g_nCount = 0;
USERDATA g_arData[100] = { 0, }; // 초기에 데이터를 받는 것.

HANDLE g_hDev;

DWORD WINAPI ProcessData(LPVOID p)
{
	USERDATA* ProcessedData = (USERDATA*)p;

	//1. 데이터 가공
	CString strTemp;
	for (int i = 0; i < 100; i++)
	{
		ProcessedData[i].x = ProcessedData[i].x * 2;
		ProcessedData[i].y = ProcessedData[i].y * 2;
		strTemp.Format(_T("x=%d, y=%d\n"), ProcessedData[i].x, ProcessedData[i].y);
		::OutputDebugString(strTemp);
	}

	//2. 서버접속 시도
	HANDLE hPipe;
	
	for (;;) // 서버 무한 접속 시도
	{
		hPipe = CreateFile(_T("\\\\.\\pipe\\MyDevPipe"),
			GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);

		if (hPipe != INVALID_HANDLE_VALUE)
		{
			break;
		}
	}
	
	//3. 데이터 전송
	DWORD dwWritten;
	TCHAR szOutput[255];
	BOOL bSuccess = TRUE; 
	CString strTemp2;
	
	for (int i = 0; i < 100; i++)
	{
		strTemp2.Format(_T("%d, %d"), ProcessedData[i].x , ProcessedData[i].y);

		bSuccess = WriteFile(hPipe, strTemp2,
			(lstrlen(strTemp2) + 1) * sizeof(CString),
			&dwWritten, NULL);


		if ((bSuccess == FALSE) || (dwWritten == 0))
		{
			break;
		}
	}
	

	//4. 뒷정리
	free(ProcessedData);
	CloseHandle(hPipe);

	return 0;
}

DWORD WINAPI SensorData(LPVOID p)
{
	int x;
	int y;

	for (;;)
	{
		Sleep(100);

		if (::GetMyDevPosition(&x, &y))
		{ 
			g_arData[g_nCount].x = x;
			g_arData[g_nCount].y = y;
			g_nCount++;
		}
		else
		{
			CString strTemp;
			strTemp.Format(_T("에러발생 : %d\n"), GetMyDevError());
		}

		if (g_nCount == 100)
		{
			DWORD dwID;
			USERDATA* arrCopy = (USERDATA*)malloc(sizeof(g_arData)); // 데이터 잡아주고
			memcpy(arrCopy, g_arData, sizeof(g_arData)); // 복사

			CreateThread(NULL, 0, ProcessData, arrCopy, 0 , &dwID);
			g_nCount = 0;
		}
	}
	
	return 0;
}


void CMyDevClientDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bState = InitMyDev(0);
	if (bState == FALSE)
	{
		AfxMessageBox(_T("초기화에 실패하였습니다."));
		return;
	}

	DWORD dwID;
	g_hDev = CreateThread(NULL, 0, SensorData, 0, 0, &dwID);	
}


void CMyDevClientDlg::OnBnClickedButton2()
{
	static BOOL bSwitch = TRUE;
	if (bSwitch == TRUE)
	{
		SuspendThread(g_hDev);
		bSwitch = FALSE;
	}
	else
	{
		ResumeThread(g_hDev);
		bSwitch = TRUE;
	}
}


void CMyDevClientDlg::OnBnClickedButton3()
{
	ReleaseMyDev();

	TerminateThread(g_hDev, 0);
	CloseHandle(g_hDev);
}
