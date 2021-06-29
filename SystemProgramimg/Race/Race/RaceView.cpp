
// RaceView.cpp: CRaceView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Race.h"
#endif

#include "RaceDoc.h"
#include "RaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRaceView

IMPLEMENT_DYNCREATE(CRaceView, CView)

BEGIN_MESSAGE_MAP(CRaceView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CRaceView 생성/소멸

// 크리티컬 섹션(CS)을 이용한 방식
CRITICAL_SECTION cs; // 열쇠 생성

// 뮤텍스를 이용한 방식
HANDLE hMutex;

CRaceView::CRaceView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// 크리티컬 섹션(CS)을 이용한 방식
	InitializeCriticalSection(&cs); // 열쇠 초기화

	// 뮤텍스를 이용한 방식
	hMutex = CreateMutex(NULL, FALSE, NULL);
}

CRaceView::~CRaceView()
{
	// 크리티컬 섹션(CS)을 이용한 방식
	DeleteCriticalSection(&cs); // 열쇠 소멸

	// 뮤텍스를 이용한 방식
	CloseHandle(hMutex);	
}

BOOL CRaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CRaceView 그리기

void CRaceView::OnDraw(CDC* /*pDC*/)
{
	CRaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CRaceView 인쇄

BOOL CRaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CRaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CRaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CRaceView 진단

#ifdef _DEBUG
void CRaceView::AssertValid() const
{
	CView::AssertValid();
}

void CRaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRaceDoc* CRaceView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRaceDoc)));
	return (CRaceDoc*)m_pDocument;
}
#endif //_DEBUG


// CRaceView 메시지 처리기


int X;

// 폴링(Polling) - 전통적인 동기화 방식
BOOL Wait = FALSE;
/*
	부작용 발생
	 => 원자성을 가지지 못했기 때문. (한 줄이 아니라 두 줄이기 떄문에)
		대기하는 문장 while문에서 Wait로 변하는 그 짧은 순간에 뺏기기 때문.
*/


DWORD WINAPI ThreadDog(LPVOID p)
{
	CRaceView* pView = (CRaceView*)p;
	CDC* pDC = pView->GetDC();

	// 폴링(Polling) - 전통적인 동기화 방식
	/*
	for (int i = 0; i < 100; i++)
	{
		while (Wait == TRUE) { ; }
		Wait = TRUE;
		
		X = 100;
		Sleep(1);
		pDC->TextOutW(X, 100, _T("개"));

		Wait = FALSE;
	}
	*/
	// 크리티컬 섹션(CS)을 이용한 방식
	/*
	for (int i = 0; i < 100; i++)
	{
		EnterCriticalSection(&cs); // 문을 열기 위해 열쇠를 빌려서 여는 것.

		X = 100;
		Sleep(1);
		pDC->TextOutW(X, 100, _T("개"));

		LeaveCriticalSection(&cs); // 문을 닫기 위해 열쇠를 빼고 돌려주는 것.
	}
	*/
	// 뮤텍스를 이용한 방식
	for (int i = 0; i < 100; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);

		X = 100;
		Sleep(1);
		pDC->TextOutW(X, 100, _T("개"));

		ReleaseMutex(hMutex);
	}
	//AfxMessageBox(_T("개가 종료되었습니다."));
	pView->ReleaseDC(pDC);
	return 0;
}

DWORD WINAPI ThreadCat(LPVOID p)
{
	CRaceView* pView = (CRaceView*)p;
	CDC* pDC = pView->GetDC();

	// 폴링(Polling) - 전통적인 동기화 방식
	/*
	for (int i = 0; i < 100; i++)
	{
		while (Wait == TRUE) { ; }
		Wait = TRUE;

		X = 200;
		Sleep(1);
		pDC->TextOutW(X, 200, _T("고양이"));

		Wait = FALSE;
	}
	*/
	// 크리티컬 섹션(CS)을 이용한 방식
	/*
	for (int i = 0; i < 100; i++)
	{
		EnterCriticalSection(&cs); // 문을 열기 위해 열쇠를 빌려서 여는 것.

		X = 200;
		Sleep(1);
		pDC->TextOutW(X, 200, _T("고양이"));

		LeaveCriticalSection(&cs); // 문을 닫기 위해 열쇠를 빼고 돌려주는 것.
	}
	*/
	// 뮤텍스를 이용한 방식
	for (int i = 0; i < 100; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);

		X = 200;
		Sleep(1);
		pDC->TextOutW(X, 200, _T("고양이"));

		ReleaseMutex(hMutex);
	}
	//AfxMessageBox(_T("고양이가 종료되었습니다."));
	pView->ReleaseDC(pDC);
	return 0;
}


void CRaceView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	DWORD dwID;

	//CloseHandle(CreateThread(NULL, 0, ThreadDog, this, 0, &dwID));
	//CloseHandle(CreateThread(NULL, 0, ThreadCat, this, 0, &dwID));
	HANDLE hAnimal[2];

	hAnimal[0] = CreateThread(NULL, 0, ThreadDog, this, 0, &dwID);
	hAnimal[1] = CreateThread(NULL, 0, ThreadCat, this, 0, &dwID);

	// 두 스레드가 종료되면 종료메시지를 출력한다.
	//DWORD dw = WaitForMultipleObjects(2, hAnimal, TRUE, INFINITE);
	//AfxMessageBox(_T("개와 고양이가 종료되었습니다."));

	DWORD dw = WaitForMultipleObjects(2, hAnimal, FALSE, INFINITE);
	switch (dw)
	{
	case WAIT_OBJECT_0 + 0:
		AfxMessageBox(_T("개가 종료되었습니다."));
		break;
	case WAIT_OBJECT_0 + 1:
		AfxMessageBox(_T("고양이가 종료되었습니다."));
		break;
	}

	CloseHandle(hAnimal[0]);
	CloseHandle(hAnimal[1]);
	CView::OnLButtonDown(nFlags, point);
}
