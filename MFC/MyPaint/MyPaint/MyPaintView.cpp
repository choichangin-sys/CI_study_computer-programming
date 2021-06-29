
// MyPaintView.cpp: CMyPaintView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MyPaint.h"
#endif

#include "MyPaintDoc.h"
#include "MyPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPaintView

IMPLEMENT_DYNCREATE(CMyPaintView, CView)

BEGIN_MESSAGE_MAP(CMyPaintView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_COMMAND(ID_LINE, &CMyPaintView::OnLine)
	ON_COMMAND(ID_RECT, &CMyPaintView::OnRect)
	ON_COMMAND(ID_ELLIPSE, &CMyPaintView::OnEllipse)
	ON_COMMAND(ID_FILL, &CMyPaintView::OnFill)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CMyPaintView::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_RECT, &CMyPaintView::OnUpdateRect)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CMyPaintView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_FILL, &CMyPaintView::OnUpdateFill)
END_MESSAGE_MAP()

// CMyPaintView 생성/소멸

CMyPaintView::CMyPaintView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_ptStart.x = 0;
	m_ptStart.y = 0;
	m_ptEnd.x = 0;
	m_ptEnd.y = 0;
	m_bDrag = FALSE;

	/********************/
	m_nShape = 0;
	m_bFill = FALSE;
	/********************/
}

CMyPaintView::~CMyPaintView()
{
}

BOOL CMyPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMyPaintView 그리기

void CMyPaintView::OnDraw(CDC* /*pDC*/)
{
	CMyPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMyPaintView 인쇄

BOOL CMyPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMyPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMyPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMyPaintView 진단

#ifdef _DEBUG
void CMyPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CMyPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPaintDoc* CMyPaintView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPaintDoc)));
	return (CMyPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyPaintView 메시지 처리기


void CMyPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	m_bDrag = TRUE;
	m_ptStart.x = point.x;
	m_ptStart.y = point.y;

	CView::OnLButtonDown(nFlags, point);
}


void CMyPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag == TRUE)
	{
		//m_bDrag = FALSE;

		m_ptEnd.x = point.x;
		m_ptEnd.y = point.y;
		RedrawWindow();
	}

	CView::OnMouseMove(nFlags, point);
}


void CMyPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (m_bDrag == TRUE)
	{
		m_bDrag = FALSE;

		m_ptEnd.x = point.x;
		m_ptEnd.y = point.y;
		RedrawWindow();
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMyPaintView::OnPaint()
{
	CPaintDC dc(this); 
	// device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CBrush* pOldBrush = nullptr;
	CBrush MyBrush(RGB(255, 0, 0));

	if (m_bFill == TRUE)
	{
		pOldBrush = dc.SelectObject(&MyBrush);
	}

	/////////////////////////////////////////
	if (m_nShape == 0)
	{
		dc.MoveTo(m_ptStart.x, m_ptStart.y);
		dc.LineTo(m_ptEnd.x, m_ptEnd.y);
	}
	else if (m_nShape == 1)
	{
		dc.Rectangle(m_ptStart.x, m_ptStart.y, 
					 m_ptEnd.x, m_ptEnd.y);
	}
	else if (m_nShape == 2)
	{
		dc.Ellipse(m_ptStart.x, m_ptStart.y, 
			       m_ptEnd.x, m_ptEnd.y);
	}
	/////////////////////////////////////////

	if (m_bFill == TRUE)
	{
		dc.SelectObject(pOldBrush);
	}
	// 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
}


void CMyPaintView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nShape = 0;
}


void CMyPaintView::OnRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nShape = 1;
}


void CMyPaintView::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nShape = 2;
}


void CMyPaintView::OnFill()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_bFill == TRUE) { m_bFill = FALSE; }
	else { m_bFill = TRUE; }
}


void CMyPaintView::OnUpdateLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_nShape == 0) { pCmdUI->SetCheck(1); }
	else { pCmdUI->SetCheck(0); }
}


void CMyPaintView::OnUpdateRect(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_nShape == 1) { pCmdUI->SetCheck(1); }
	else { pCmdUI->SetCheck(0); }
}


void CMyPaintView::OnUpdateEllipse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_nShape == 2) { pCmdUI->SetCheck(1); }
	else { pCmdUI->SetCheck(0); }
}


void CMyPaintView::OnUpdateFill(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_bFill) { pCmdUI->SetCheck(1); }
	else { pCmdUI->SetCheck(0); }
}
