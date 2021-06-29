
// MultiTaskView.cpp: CMultiTaskView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MultiTask.h"
#endif

#include "MultiTaskDoc.h"
#include "MultiTaskView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMultiTaskView

IMPLEMENT_DYNCREATE(CMultiTaskView, CView)

BEGIN_MESSAGE_MAP(CMultiTaskView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMultiTaskView 생성/소멸

CMultiTaskView::CMultiTaskView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMultiTaskView::~CMultiTaskView()
{
}

BOOL CMultiTaskView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMultiTaskView 그리기

int g_nBlue;

void CMultiTaskView::OnDraw(CDC* pDC)
{
	CMultiTaskDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMultiTaskView 인쇄

BOOL CMultiTaskView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMultiTaskView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMultiTaskView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMultiTaskView 진단

#ifdef _DEBUG
void CMultiTaskView::AssertValid() const
{
	CView::AssertValid();
}

void CMultiTaskView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultiTaskDoc* CMultiTaskView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultiTaskDoc)));
	return (CMultiTaskDoc*)m_pDocument;
}
#endif //_DEBUG


// CMultiTaskView 메시지 처리기
CMultiTaskView* g_pView;

DWORD WINAPI ThreadDraw(LPVOID p) // 함수의 영역 외우기. 시험의 출제 가능성 100%.
{
	RECT rc = *(LPRECT)p;
	CDC* pDC = g_pView->GetDC();
	// getexitcodethread = 스레드의 종료를 알 수 있는 함수
	// suspendthread = 잠시 중지
	// resumethread = 다시 시작
	while (1)
	{
		g_nBlue += 5;

		if (g_nBlue > 255)
		{
			g_nBlue = 0;
		}

		CBrush brBlue(RGB(0, 0, g_nBlue));
		CBrush* pOldBr = pDC->SelectObject(&brBlue);
		pDC->Rectangle(rc.left, rc.top, rc.right, rc.bottom);
		pDC->SelectObject(pOldBr);
	}

	g_pView->ReleaseDC(pDC);
	return 0;
}

void CMultiTaskView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	g_pView = this;

	static RECT arRect[] = { {100, 100, 200, 200},
							 {300, 100, 400, 200},
							 {100, 300, 200, 400},
							 {300, 300, 400, 400}, };

	DWORD dwID;
	for (int i = 0; i < 4; i++)
	{
		CloseHandle(CreateThread(NULL, 0, 
								ThreadDraw, &arRect[i],
								0, &dwID)); // 알아서 하고 가겠지. 제어할 의사가 없음.
	}
	
	CView::OnLButtonDown(nFlags, point);
}