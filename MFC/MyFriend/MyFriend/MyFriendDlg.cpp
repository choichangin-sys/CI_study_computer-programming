
// MyFriendDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MyFriend.h"
#include "MyFriendDlg.h"
#include "afxdialogex.h"
#include "CPerson.h"

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


// CMyFriendDlg 대화 상자



CMyFriendDlg::CMyFriendDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYFRIEND_DIALOG, pParent)
	, m_strName(_T(""))
	, m_nAge(0)
	, m_bSex(FALSE) // TRUE인 경우에 여성이 됨.
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCount = 0;
}

void CMyFriendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_AGE, m_nAge);
	DDX_Radio(pDX, IDC_RADIO_MALE, m_bSex);
	
	DDX_Control(pDX, IDC_FRIENDLIST, m_ctrlFriend); 
	DDX_Control(pDX, IDC_SPIN_AGE, m_ctrlSpin);
}

BEGIN_MESSAGE_MAP(CMyFriendDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADDPERSON, &CMyFriendDlg::OnBnClickedButtonAddperson)
	ON_NOTIFY(HDN_ENDFILTEREDIT, 0, &CMyFriendDlg::OnHdnEndFilterEditFriendlist)
	ON_BN_CLICKED(IDC_LOAD_PERSON, &CMyFriendDlg::OnBnClickedLoadPerson)
	ON_BN_CLICKED(IDC_SAVE_PERSON, &CMyFriendDlg::OnBnClickedSavePerson)
END_MESSAGE_MAP()


// CMyFriendDlg 메시지 처리기

BOOL CMyFriendDlg::OnInitDialog()
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
	m_ctrlSpin.SetRange(0, 100);
	m_ctrlSpin.SetPos(0);
	m_nCount = 0;

	/*************************************************************************/
	// 상위(맨 첫 번째 표기란)칸 만들기.
	m_ctrlFriend.InsertColumn(0, _T("이름"), 0, 150);
	m_ctrlFriend.InsertColumn(1, _T("나이"), 0, 50);
	m_ctrlFriend.InsertColumn(2, _T("성별"), 0, 100);
	/*************************************************************************/

	/*************************************************************************/
	// List Style 변환
	//m_ctrlFriend.ModifyStyle(LVS_TYPEMASK, LVS_REPORT); // 스타일을 변환. 속성에서 추가 할 수 있음.
	/*************************************************************************/

	/*************************************************************************/
	// CheckBox 추가
	DWORD dwStyle = m_ctrlFriend.GetExtendedStyle();
	m_ctrlFriend.SetExtendedStyle(dwStyle | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	/*************************************************************************/

	/*****************************************************************/
	// TEST
	//m_ctrlFriend.InsertItem(0, _T("박명수"), 1);
	//m_ctrlFriend.SetItemText(0, 1, _T("50"));
	//m_ctrlFriend.SetItemText(0, 2, _T("남성"));
	/*****************************************************************/

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMyFriendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyFriendDlg::OnPaint()
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
HCURSOR CMyFriendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyFriendDlg::OnBnClickedButtonAddperson()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nCount >= 5)
	{
		AfxMessageBox(_T("더 이상 추가할 수 없습니다."));
		return;
	}
	else
	{
		// 1. 데이터 얻어오기. 이름, 나이, 성별
		UpdateData(1);

		// 2. 얻은 데이터를 m_ctrlFriend에 친구를 추가함.
		CString strAge;
		strAge.Format(_T("%d"), m_nAge);

		CString strSex;
		if (m_bSex == TRUE) { strSex = _T("여성"); }
		else { strSex = _T("남성"); }

		m_ctrlFriend.InsertItem(0, m_strName);
		m_ctrlFriend.SetItemText(0, 1, strAge);
		m_ctrlFriend.SetItemText(0, 2, strSex);

		// 3. 메모리에 추가

		m_pPerson[m_nCount].m_strName = m_strName;
		m_pPerson[m_nCount].m_nAge = m_nAge;
		m_pPerson[m_nCount].m_bGender = m_bSex;
		m_nCount++;
	}
	// 4.초기화하기
	m_strName = _T("");
	m_nAge = 0;
	m_bSex = FALSE;
	UpdateData(0);//컨트롤 <-- 변수

}


void CMyFriendDlg::OnHdnEndFilterEditFriendlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEdit* pEdit = m_ctrlFriend.GetEditControl();

	CString strTemp;
	pEdit->GetWindowText(strTemp);

	//AfxMessageBox(strTemp);
	//m_ctrlFriend.SetItemText(pDispInfo->item.iItem, 0, strTemp);

	*pResult = 0;
}

#include "CSaveFileNameDlg.h"

void CMyFriendDlg::OnBnClickedSavePerson()
{
	// 대화상자 만들기
	CFileDialog dlg(FALSE);
	if (dlg.DoModal() == MB_OK) return;
	
	/********************************************************/
	// 1. 데이터 저장하기
	CFile file(dlg.GetPathName(),
		CFile::modeCreate | CFile::modeReadWrite);
	CArchive ar(&file, CArchive::store);

	ar << m_nCount;

	for (int i = 0; i < m_nCount; i++)
	{
		m_pPerson[i].Serialize(ar);
	}

	// 2. 메모리(m_pPerson)와 화면(ListCtrl) 초기화
	// 내가 한 방식
	/*
	for (int i = m_nCount - 1; i >= 0; i--)
	{
		m_ctrlFriend.DeleteItem(i);
		m_pPerson[i].m_strName = _T("");
		m_pPerson[i].m_nAge = 0;
		m_pPerson[i].m_bGender = FALSE;
	}

	m_nCount = 0;
	*/
	// 강사님 방식
	m_nCount = 0;
	m_ctrlFriend.DeleteAllItems();
}


void CMyFriendDlg::OnBnClickedLoadPerson()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == MB_OK) return;
	/******************************************/
	// 0. 다시 불렀을 때 화면 초기화
	m_nCount = 0;
	m_ctrlFriend.DeleteAllItems();
	/******************************************/
	// 1. 데이터 불러오기
	CFile file(dlg.GetPathName(),
		CFile::modeReadWrite);

	CArchive ar(&file, CArchive::load);

	ar >> m_nCount;

	for (int i = 0; i < m_nCount; i++)
	{
		m_pPerson[i].Serialize(ar);
	}

	/******************************************/
	// 2. 화면(ListCtrl)에 표시
	for (int i = 0; i < m_nCount; i++)
	{
		CString strAge;
		strAge.Format(_T("%d"), m_pPerson[i].m_nAge);

		CString strSex;
		if (m_pPerson[i].m_bGender == TRUE) { strSex = _T("여성"); }
		else { strSex = _T("남성"); }

		m_ctrlFriend.InsertItem(0, m_pPerson[i].m_strName);
		m_ctrlFriend.SetItemText(0, 1, strAge);
		m_ctrlFriend.SetItemText(0, 2, strSex);
	}
}