
// AsyncIODlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "AsyncIO.h"
#include "AsyncIODlg.h"
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


// CAsyncIODlg 대화 상자



CAsyncIODlg::CAsyncIODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASYNCIO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsyncIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAsyncIODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAsyncIODlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAsyncIODlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAsyncIODlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAsyncIODlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAsyncIODlg 메시지 처리기

BOOL CAsyncIODlg::OnInitDialog()
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

void CAsyncIODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAsyncIODlg::OnPaint()
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
HCURSOR CAsyncIODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

char strData[] =
"나룻배와 행인\r\n"
"			한용운\r\n"
"나는 나룻배\r\n"
"당신은 행인\r\n"
"당신은 흙발로 나를 짓밟습니다.\r\n"
"나는 당신을 안고 물을 건너갑니다.\r\n"
"나는 당신을 안으면 깊으나 얕으나 급한 여울이나 건너갑니다.\r\n"
"만일 당신이 아니 오시면 나는 바람을 쐬고 눈비를 맞으며\r\n"
"밤에서 낮까지 당신을 기다리고 있습니다.\r\n"
"당신은 물만 건너면 나를 보지도 않고 가십니다 그려.\r\n"
"그러나 당신이 언제든지 오실 줄만은 알아요.\r\n"
"나는 당신을 기다리면서 날마다 날마다 낡아 갑니다.\r\n"
"나는 나룻배\r\n"
"당신은 행인\r\n";

void CAsyncIODlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	HANDLE hFile;
	hFile = CreateFile(_T("c:\\temp\\event_io.txt"),
						GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0); 
	// FILE_FLAG_OVERLAPPED 이게 없으면 비동기로 안돌음.
	DWORD dwWritten = 0;

	OVERLAPPED ov1 = { 0, };
	ov1.Offset = (strlen(strData) * sizeof(char)) * 0;
	ov1.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	OVERLAPPED ov2 = { 0, };
	ov2.Offset = (strlen(strData) * sizeof(char)) * 1;
	ov2.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	OVERLAPPED ov3 = { 0, };
	ov3.Offset = (strlen(strData) * sizeof(char)) * 2;
	ov3.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//BOOL bReturn = WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov);

	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov1);
	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov2);
	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov3);

	/*
	// IO결과를 기다린다.. (결과 확인을 위해 기다린다.)
	if ((bReturn == FALSE) && (GetLastError()) == ERROR_IO_PENDING)
	{
		AfxMessageBox(_T("IO가 정상적으로 요청되었습니다."));
	}
	*/
	// 다른 작업을 할 기회~~~ (강의 : IO 결과를 기다린다)
	// WaitForSingleObject(hFile, INFINITE);
	// WaitForSingleObject(ov.hEvent, INFINITE);

	HANDLE h[3] = { ov1.hEvent,ov2.hEvent,ov3.hEvent };
	WaitForMultipleObjects(3, h, TRUE, INFINITE);

	if (GetOverlappedResult(hFile, &ov1, &dwWritten, FALSE))
	{
		CString strTemp;
		strTemp.Format(_T("1번 비동기 IO 결과 : %d"), dwWritten);
		AfxMessageBox(strTemp);
	}
	
	if (GetOverlappedResult(hFile, &ov2, &dwWritten, FALSE))
	{
		CString strTemp;
		strTemp.Format(_T("2번 비동기 IO 결과 : %d"), dwWritten);
		AfxMessageBox(strTemp);
	}

	if (GetOverlappedResult(hFile, &ov3, &dwWritten, FALSE))
	{
		CString strTemp;
		strTemp.Format(_T("3번 비동기 IO 결과 : %d"), dwWritten);
		AfxMessageBox(strTemp);
	}

	CloseHandle(hFile);
}

void WINAPI MyFunc(DWORD dwerr, DWORD dwByte, LPOVERLAPPED pOV)
{
	CString strTemp;
	strTemp.Format(_T("[%s]비동기 IO 결과 : %d"), pOV->hEvent , dwByte);
	AfxMessageBox(strTemp);
}

void CAsyncIODlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	HANDLE hFile;
	hFile = CreateFile(_T("c:\\temp\\callback_io.txt"),
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);


	OVERLAPPED ov1 = { 0, };
	ov1.Offset = (strlen(strData) * sizeof(char)) * 0;
	ov1.hEvent = (HANDLE)_T("겨울왕국");

	OVERLAPPED ov2 = { 0, };
	ov2.Offset = (strlen(strData) * sizeof(char)) * 1;
	ov2.hEvent = (HANDLE)_T("여름왕국");

	OVERLAPPED ov3 = { 0, };
	ov3.Offset = (strlen(strData) * sizeof(char)) * 2;
	ov3.hEvent = (HANDLE)_T("가을왕국");

	WriteFileEx(hFile, strData, sizeof(strData), &ov1, MyFunc);
	WriteFileEx(hFile, strData, sizeof(strData), &ov2, MyFunc);
	WriteFileEx(hFile, strData, sizeof(strData), &ov3, MyFunc);

	SleepEx(1, TRUE); // 알림가능한 상태로 변경함

	CloseHandle(hFile);
}

#define MEGADATA 100
#define MEGA 1048576
#pragma warning (disable:4996)

char* buf;
DWORD len;
HANDLE g_hMegaEvent;

DWORD WINAPI MakeBigData(LPVOID p1)
{
	buf = (char*)calloc(MEGADATA, MEGA);

	if (buf == NULL)
	{
		AfxMessageBox(_T("메모리 할당 실패"));

		return -1;
	}

	char* p = NULL;

	char sTmp[256];
	int tlen;
	p = buf;

	for (int i = 1;; i++)
	{
		sprintf(sTmp, ("%dLune : this file is a test\r\n"), i);
		tlen = strlen(sTmp);

		if (p - buf + tlen >= MEGADATA * MEGA)
		{
			break;
		}

		strcpy(p, sTmp);
		p += tlen;
	}
	len = p - buf;

	// 우체통 사용 방식
	SetEvent(g_hMegaEvent);
	/////////////////////////////////////////////////////

	return 0;
}


DWORD WINAPI WriteBigData(LPVOID p2)
{
	// 우체통 사용 방식
	WaitForSingleObject(g_hMegaEvent, INFINITE);
	/////////////////////////////////////////////////////
	HANDLE hBigFile;
	hBigFile = CreateFile(_T("c:\\temp\\BigFile.txt"),
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	OVERLAPPED ov = { 0, };
	ov.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	BOOL bReturn = WriteFile(hBigFile, buf, len, NULL, &ov);
	if (bReturn == FALSE && GetLastError() == ERROR_IO_PENDING)
	{
		AfxMessageBox(_T("IO가 정상적으로 작동하였습니다."));
	}

	// IO 완료 통지(Event)를 기다려..
	DWORD dwWritten = 0;
	WaitForSingleObject(ov.hEvent, INFINITE);
	if (GetOverlappedResult(hBigFile, &ov, &dwWritten, FALSE))
	{
		CString strTemp;
		strTemp.Format(_T("BigFile 비동기 IO 결과 : %d"), dwWritten);
		AfxMessageBox(strTemp);
	}


	CloseHandle(hBigFile);
	free(buf);

	return 0;
}

void CAsyncIODlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD ID;

	HANDLE bMakeBigData = CreateThread(0, 0, MakeBigData, 0, 0, &ID);
	WaitForSingleObject(bMakeBigData, INFINITE);

	HANDLE bCreateThread = CreateThread(0, 0, WriteBigData, 0, 0, &ID);
	WaitForSingleObject(bCreateThread, INFINITE);

	CloseHandle(bCreateThread);
	CloseHandle(bMakeBigData);

	// 우체통 사용 방식
	/*
	g_hMegaEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//or g_hMegaEvent = CreateThread(0, 0, MakeBigData, 0, 0, &ID);
	*/

}


void CAsyncIODlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 1. 소스파일의 MMF(변수)를 생성한다.
	HANDLE hSrc;
	hSrc = CreateFile(_T("c:\\temp\\BigFile.txt"), 
		GENERIC_READ, 0, NULL, OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL, NULL);

	// 1-0. 파일 사이즈 구한다.
	LARGE_INTEGER llFileSize;
	GetFileSizeEx(hSrc, &llFileSize);

	// 1-1. MMF 1단계
	HANDLE hMMF;
	hMMF = CreateFileMapping(hSrc, NULL, PAGE_WRITECOPY,
		0, 0, NULL);

	// 1-2. MMF 2단계
	BYTE* pText = (BYTE*)MapViewOfFile(hMMF, FILE_MAP_READ,
			0, 0, // 전체 연결한다는 의미
			0);

	// 2. 타겟파일로 비동기 복사한다. ( WriteEX() )
	HANDLE hDest;
	hDest = CreateFile(_T("c:\\temp\\BigFileCopy.txt"), 
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

	OVERLAPPED ov = { 0, };
	
	ov.hEvent = (HANDLE)_T("빅카피");
	WriteFileEx(hDest, pText, llFileSize.QuadPart, &ov, MyFunc);

	SleepEx(1, TRUE); // 알림가능한 상태로 전환

	// 3. 뒷정리한다.
	UnmapViewOfFile(pText);
	CloseHandle(hSrc);
	CloseHandle(hDest);
	CloseHandle(hMMF);
}
