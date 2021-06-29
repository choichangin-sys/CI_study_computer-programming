﻿
// CreateDemoView.cpp: CCreateDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CreateDemo.h"
#endif

#include "CreateDemoDoc.h"
#include "CreateDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCreateDemoView

IMPLEMENT_DYNCREATE(CCreateDemoView, CView)

BEGIN_MESSAGE_MAP(CCreateDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP() // 스위치문의 케이스 같은 느낌.

// CCreateDemoView 생성/소멸

CCreateDemoView::CCreateDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCreateDemoView::~CCreateDemoView()
{
}

BOOL CCreateDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCreateDemoView 그리기

void CCreateDemoView::OnDraw(CDC* /*pDC*/)
{
	CCreateDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCreateDemoView 인쇄

BOOL CCreateDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCreateDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCreateDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCreateDemoView 진단

#ifdef _DEBUG
void CCreateDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCreateDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCreateDemoDoc* CCreateDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCreateDemoDoc)));
	return (CCreateDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CCreateDemoView 메시지 처리기

//int CCreateDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CView::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
//
//	return 0;
//}


int CCreateDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_WndChild.Create(_T("Button"), _T("최창인"),
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		CRect(30, 30, 180, 180),
		this, //GetDesktopWindow(),
		1234);
	return 0;
}


void CCreateDemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
	SendMessage(WM_CLOSE);

	CView::OnLButtonDown(nFlags, point);
}


void CCreateDemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 1. 현재 버튼의 위치를 구한다.
	CRect RectButton;
	m_WndChild.GetWindowRect(&RectButton); // this를 안써도 앞에 붙어있다.
	// 위에서(GetWindowRect)에서 스크린 좌표계를 사용함.
	ScreenToClient(&RectButton); // 클라이언트 좌표계로 바꿔야함.
	//ClientToScreen // 클라이언트 좌표계를 스크린 좌표계로.

	int x = RectButton.left;
	int y = RectButton.top;
	int w = RectButton.Width();
	//int w = RectButton.right - RectButton.left;

	int h = RectButton.Height();
	//int h = RectButton.bottom - RectButton.top;

	// 2. 그 위치에서 -/+ 10씩 계산한다.
	if (nChar == VK_LEFT)
	{
		x -= 10;
		w -= 10;
	}
	else if (nChar == VK_RIGHT)
	{
		x += 10;
		w += 10;;
	}

	// 3. 버튼을 계산된 위치로 이동한다.
	m_WndChild.SetWindowPos(NULL, x, y, w, h,
		SWP_NOZORDER | SWP_SHOWWINDOW);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCreateDemoView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTemp;
	strTemp.Format(TEXT("%d, %c 키 눌림"), nChar, nChar); //printf와 같음. Format
	//AfxMessageBox(strTemp);
	m_WndChild.SetWindowText(strTemp); // 버튼에다 씀
	SetWindowText(strTemp); // 뷰에다 씀
	AfxGetMainWnd()->SetWindowText(strTemp); // 액자에다 씀

	CView::OnChar(nChar, nRepCnt, nFlags);
}
