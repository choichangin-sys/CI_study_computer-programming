﻿
// RangeDEmoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "RangeDEmo.h"
#include "RangeDEmoDlg.h"
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
public:
	afx_msg void OnNMReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, &CAboutDlg::OnNMReleasedcaptureSlider)
END_MESSAGE_MAP()


// CRangeDEmoDlg 대화 상자



CRangeDEmoDlg::CRangeDEmoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RANGEDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//m_ctrlProgress.SetRange(0, 100);
	//m_ctrlProgress.SetPos(50);
}

void CRangeDEmoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
	DDX_Control(pDX, IDC_SLIDER, m_nctrlSlider);
	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);
}

BEGIN_MESSAGE_MAP(CRangeDEmoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, &CRangeDEmoDlg::OnNMReleasedcaptureSlider)
	ON_EN_UPDATE(IDC_EDIT1, &CRangeDEmoDlg::OnEnUpdateEdit1)
END_MESSAGE_MAP()


// CRangeDEmoDlg 메시지 처리기

BOOL CRangeDEmoDlg::OnInitDialog()
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
	m_ctrlProgress.SetRange(0, 100);
	m_ctrlProgress.SetPos(50);
	m_nctrlSlider.SetRange(0, 100);
	m_nctrlSlider.SetPos(50);
	m_nctrlSlider.SetTicFreq(10);
	m_ctrlSpin.SetRange(0, 100);
	m_ctrlSpin.SetPos(50);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRangeDEmoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRangeDEmoDlg::OnPaint()
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
HCURSOR CRangeDEmoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnNMReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	// 1. 값 받아오기.
	

	// 2. 받은 값 전달하기.
	
}


void CRangeDEmoDlg::OnNMReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 1. 슬라이더의 값을 읽는다.
	int nPos = m_nctrlSlider.GetPos();

	// 2. 그 값으로 프로그레스에 쓴다.
	m_ctrlProgress.SetPos(nPos);
	m_ctrlSpin.SetPos(nPos);
	*pResult = 0;
}




void CRangeDEmoDlg::OnEnUpdateEdit1()
{
	if (m_ctrlSpin.GetSafeHwnd())
	{
		// 1. 스핀의 값을 구한다.
		int nPos = m_ctrlSpin.GetPos();

		// 2. 그 값으로 프로그래스와 슬라이더에 쓴다.
		m_ctrlProgress.SetPos(nPos);
		m_nctrlSlider.SetPos(nPos);
	}
}
