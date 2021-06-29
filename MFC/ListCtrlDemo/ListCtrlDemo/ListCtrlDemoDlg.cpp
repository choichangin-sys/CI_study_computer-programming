
// ListCtrlDemoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ListCtrlDemo.h"
#include "ListCtrlDemoDlg.h"
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


// CListCtrlDemoDlg 대화 상자



CListCtrlDemoDlg::CListCtrlDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LISTCTRLDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 리모컨(변수컨트롤)은 여기가 아님.
	//m_ctrlFriend.InsertItem(0, _T("유재석"));
	//m_ctrlFriend.InsertItem(1, _T("박명수"));
}

void CListCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FRIEND, m_ctrlFriend);
}

BEGIN_MESSAGE_MAP(CListCtrlDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CListCtrlDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CListCtrlDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CListCtrlDemoDlg::OnBnClickedButton3)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_FRIEND, &CListCtrlDemoDlg::OnLvnEndlabeleditFriend)
END_MESSAGE_MAP()


// CListCtrlDemoDlg 메시지 처리기

BOOL CListCtrlDemoDlg::OnInitDialog()
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
	// 리포트 스타일은 가장 많은 정보를 제공하지만 컬럼이 없으면 나오지 않는다. 그렇기에 컬럼을 추가해줘야한다.
	m_ctrlFriend.InsertColumn(0, _T("이름"),0, 100);
	m_ctrlFriend.InsertColumn(1, _T("주소"), 0, 200);
	m_ctrlFriend.InsertColumn(2, _T("전화번호"), 0, 200);
	/*********************************************************/
	// 이미지 리스트 사용
	// 1. 빈 방을 생성한다.
	static CImageList imgListSmall;
	imgListSmall.Create(16, 16, ILC_COLOR32, 5, 0);

	// 2. 각 방에서 이미지를 추가한다. (ICO, BMP)
	imgListSmall.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	imgListSmall.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	imgListSmall.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	imgListSmall.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	imgListSmall.Add(AfxGetApp()->LoadIcon(IDI_ICON5));

	// 3. 컨트롤과 이미지 리스트가 결합한다.
	m_ctrlFriend.SetImageList(&imgListSmall, LVSIL_SMALL);

	/*********************************************************/
	// 1. 빈 방을 생성한다.
	static CImageList imgList;
	imgList.Create(48, 48, ILC_COLOR32, 5, 0);

	// 2. 각 방에서 이미지를 추가한다. (ICO, BMP)
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));

	// 3. 컨트롤과 이미지 리스트가 결합한다.
	m_ctrlFriend.SetImageList(&imgList, LVSIL_NORMAL);

	// 4. 컨트롤은 이미지를 번호(Index)로 사용한다.
	/*********************************************************/
	m_ctrlFriend.InsertItem(0, _T("유재석"), 0);
	//m_ctrlFriend.SetItemText(0, 0, _T("유느님"));
	m_ctrlFriend.SetItemText(0, 1, _T("구래동"));
	m_ctrlFriend.SetItemText(0, 2, _T("010-1111-1111"));

	m_ctrlFriend.InsertItem(1, _T("박명수"), 1);
	m_ctrlFriend.SetItemText(1, 1, _T("장기동"));
	m_ctrlFriend.SetItemText(1, 2, _T("010-2222-2222"));

	m_ctrlFriend.InsertItem(2, _T("하하"), 3);
	m_ctrlFriend.SetItemText(2, 1, _T("사우동"));
	m_ctrlFriend.SetItemText(2, 2, _T("010-3333-3333"));

	m_ctrlFriend.InsertItem(3, _T("정준하"), 2);
	m_ctrlFriend.SetItemText(3, 1, _T("운양동"));
	m_ctrlFriend.SetItemText(3, 2, _T("010-4444-4444"));

	m_ctrlFriend.InsertItem(4, _T("정형돈"), 4);
	m_ctrlFriend.SetItemText(4, 1, _T("풍무동"));
	m_ctrlFriend.SetItemText(4, 2, _T("010-5555-5555"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CListCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListCtrlDemoDlg::OnPaint()
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
HCURSOR CListCtrlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListCtrlDemoDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static DWORD dwStyle = LVS_ICON; // 0

	dwStyle++;

	if (dwStyle > LVS_LIST) // 3보다 크니?
	{
		dwStyle = LVS_ICON; // 그럼 0으로
	}

	m_ctrlFriend.ModifyStyle(LVS_TYPEMASK, dwStyle); // 스타일을 변화 시키는 것.
}


void CListCtrlDemoDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	DWORD dwStyle = m_ctrlFriend.GetExtendedStyle();

	m_ctrlFriend.SetExtendedStyle(dwStyle
		| LVS_EX_TRACKSELECT
		| LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES
		| LVS_EX_CHECKBOXES
	);


}


void CListCtrlDemoDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nCount = m_ctrlFriend.GetItemCount();

	// Index가 있는 것은 뒤에서부터 지우는 것이 좋다.
	for (int i = nCount - 1; i >= 0; i--)
	//for (int i = 0; i < nCount; i++)
	{
		if (m_ctrlFriend.GetCheck(i) == TRUE)
		{
			m_ctrlFriend.DeleteItem(i);
			//i--;
		}
	}


}


void CListCtrlDemoDlg::OnLvnEndlabeleditFriend(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEdit* pEdit = m_ctrlFriend.GetEditControl();

	CString strTemp;
	pEdit->GetWindowText(strTemp);

	//AfxMessageBox(strTemp);
	m_ctrlFriend.SetItemText(pDispInfo->item.iItem, 0, strTemp);

	*pResult = 0;
}
