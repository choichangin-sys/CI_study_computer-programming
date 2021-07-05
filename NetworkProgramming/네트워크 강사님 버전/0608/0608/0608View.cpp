
// 0608View.cpp: CMy0608View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "0608.h"
#endif

#include "0608Doc.h"
#include "0608View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy0608View

IMPLEMENT_DYNCREATE(CMy0608View, CFormView)

BEGIN_MESSAGE_MAP(CMy0608View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy0608View::OnBnClickedButton1)
END_MESSAGE_MAP()

// CMy0608View 생성/소멸

CMy0608View::CMy0608View() noexcept
	: CFormView(IDD_MY0608_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy0608View::~CMy0608View()
{
}

void CMy0608View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMy0608View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMy0608View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMy0608View 인쇄

BOOL CMy0608View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy0608View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy0608View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy0608View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CMy0608View 진단

#ifdef _DEBUG
void CMy0608View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy0608View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy0608Doc* CMy0608View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy0608Doc)));
	return (CMy0608Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy0608View 메시지 처리기


void CMy0608View::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString msg;
	GetDlgItemText(IDC_EDIT2, msg);

	DisplayText("[%s] %s\r\n", "홍길동", msg);
}


// 에디트 컨트롤에 문자열 출력
void CMy0608View::DisplayText(char* fmt, ...)
{
	va_list arg;			va_start(arg, fmt);

	char cbuf[512 + 256];	vsprintf_s(cbuf, fmt, arg);

	//크로스 쓰레드 문제 발생!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//컨트롤을 생성한 쓰레드(primary thread)
	//컨트롤을 사용하는 쓰레드가 다를경우 발생하는 문제.
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	int nLength = pEdit->GetWindowTextLength();
	pEdit->SetSel(nLength, nLength);
	pEdit->ReplaceSel(cbuf);

	//	int nLength = m_ctrlList.GetWindowTextLength();
	//	m_ctrlList.SetSel(nLength, nLength);
	//	m_ctrlList.ReplaceSel(cbuf);

	//	int nLength = GetWindowTextLength(hEdit2);
	//	SendMessage(hEdit2, EM_SETSEL, nLength, nLength);
	//	SendMessage(hEdit2, EM_REPLACESEL, FALSE, (LPARAM)cbuf);
	va_end(arg);
}

