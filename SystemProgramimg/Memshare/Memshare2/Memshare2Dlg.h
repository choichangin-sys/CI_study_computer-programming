
// Memshare2Dlg.h: 헤더 파일
//

#pragma once


// CMemshare2Dlg 대화 상자
class CMemshare2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMemshare2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMSHARE2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 우리끼리 쓰는 메시지를 사용할 때 추가해야함.
	afx_msg LRESULT OnUserMessage1(WPARAM w, LPARAM l);
	//////////////////////////////////////////////////////
};
