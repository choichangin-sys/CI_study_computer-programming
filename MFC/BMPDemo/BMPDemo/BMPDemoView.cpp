
// BMPDemoView.cpp: CBMPDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BMPDemo.h"
#endif

#include "BMPDemoDoc.h"
#include "BMPDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBMPDemoView

IMPLEMENT_DYNCREATE(CBMPDemoView, CView)

BEGIN_MESSAGE_MAP(CBMPDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_PAINT()
ON_WM_PAINT()
END_MESSAGE_MAP()

// CBMPDemoView 생성/소멸

CBMPDemoView::CBMPDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.


}

CBMPDemoView::~CBMPDemoView()
{
}

BOOL CBMPDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBMPDemoView 인쇄

BOOL CBMPDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBMPDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBMPDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CBMPDemoView 진단

#ifdef _DEBUG
void CBMPDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CBMPDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBMPDemoDoc* CBMPDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBMPDemoDoc)));
	return (CBMPDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CBMPDemoView 그리기

void CBMPDemoView::OnDraw(CDC* pDC)
{
	CBMPDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	if (pDC->IsPrinting() == TRUE)
	{
		pDC->TextOut(10, 10, _T("쪽번호"));
	}

	CString StrTemp;
	StrTemp.Format(_T("국어 : %d"), pDoc->m_nKor);
	pDC->TextOut(10, 100, StrTemp);
	StrTemp.Format(_T("수학 : %d"), pDoc->m_nMath);
	pDC->TextOut(10, 200, StrTemp);
	StrTemp.Format(_T("영어 : %d"), pDoc->m_nEng);
	pDC->TextOut(10, 300, StrTemp);

	pDC->Rectangle(100, 100, 500, 500);
}



// CBMPDemoView 메시지 처리기


void CBMPDemoView::OnPaint()
{
	
	CPaintDC ViewDC(this); 
	// device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	// 1. ViewDC와 호환되는 MemDC를 생성한다.
	CDC MemDC;
	MemDC.CreateCompatibleDC(&ViewDC);

	// 2. MemDC에 BMP를 그린다.
	CBitmap BmpBaby;
	//BmpBaby.LoadBitmap(IDB_BABY);
	BmpBaby.LoadBitmap(IDB_TRENSPARRENT);

	BITMAP BmpInfo;
	BmpBaby.GetBitmap(&BmpInfo);



	CBitmap* pOldBmp = MemDC.SelectObject(&BmpBaby);

	//MemDC.Rectangle(100, 100, 300, 300);
	//MemDC.TextOut(10, 10, _T("엄마와 아기"));

	// 3. ViewDC로 MemDC를 내보낸다. (4가지 방법)
	// 1번 (= BitBlt)
	
	ViewDC.BitBlt(0, 0, // 그림이 그려질 시작점
					BmpInfo.bmWidth, BmpInfo.bmHeight, // MemDC에서 ViewDC 그리는 사진의 사이즈
					// 위에는 ViewDC임
					&MemDC,
					0, 0, // 그림을 뜯어오는 시작점D
					SRCCOPY);
	
	 //2번 (= StretchBlt)
	
	ViewDC.StretchBlt(0, 0,  //그림이 그려질 시작점
		BmpInfo.bmWidth, BmpInfo.bmHeight,  //MemDC에서 ViewDC 그리는 사진의 사이즈
		 //위에는 ViewDC임
		&MemDC,
		0, 0,
		BmpInfo.bmWidth, BmpInfo.bmHeight,
		SRCCOPY);
	
	 //3번 (= TransparentBlt)(색깔 지정 후, 그 색깔 모자이크(=삭제))
	
	ViewDC.TransparentBlt(0, 100,  //그림이 그려질 시작점
		BmpInfo.bmWidth, BmpInfo.bmHeight,  //MemDC에서 ViewDC 그리는 사진의 사이즈
		 //위에는 ViewDC임
		&MemDC,
		0, 0,
		BmpInfo.bmWidth, BmpInfo.bmHeight,
		RGB(0, 0, 0));

	ViewDC.TransparentBlt(0, 200,  //그림이 그려질 시작점
		BmpInfo.bmWidth, BmpInfo.bmHeight,  //MemDC에서 ViewDC 그리는 사진의 사이즈
		// 위에는 ViewDC임
		&MemDC,
		0, 0,
		BmpInfo.bmWidth, BmpInfo.bmHeight,
		RGB(255, 0, 0));
	
	 //4번 (=AlphaBlend, 포토샵 느낌. 연해짐.)
	
	BLENDFUNCTION bf = { 0 };
	bf.SourceConstantAlpha = 50;

	ViewDC.AlphaBlend(0, 300, // 그림이 그려질 시작점
		BmpInfo.bmWidth, BmpInfo.bmHeight, // MemDC에서 ViewDC 그리는 사진의 사이즈
		// 위에는 ViewDC임
		&MemDC,
		0, 0,
		BmpInfo.bmWidth, BmpInfo.bmHeight,
		bf);
	

	 //4. 뒷정리를 한다.
	MemDC.SelectObject(pOldBmp);
	
}


void CBMPDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	pDC->Ellipse(300, 300, 600, 600);

	CView::OnPrint(pDC, pInfo);
}



