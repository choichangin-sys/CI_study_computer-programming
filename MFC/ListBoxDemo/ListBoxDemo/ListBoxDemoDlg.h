
// ListBoxDemoDlg.h: 헤더 파일
//

#pragma once


// CListBoxDemoDlg 대화 상자
class CListBoxDemoDlg : public CDialogEx
{
// 생성입니다.
public:
	CListBoxDemoDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTBOXDEMO_DIALOG };
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
	afx_msg void OnBnClickedButtonAddstring();
	afx_msg void OnBnClickedButtonInsertstring();
	afx_msg void OnBnClickedButtonFindstring();
	afx_msg void OnLbnSelchangeListName();
	afx_msg void OnBnClickedButtonCall();
	CListBox m_ctrlNameBox;
	CString m_strNameAddBox;
	CButton m_bAddName;
	CComboBox m_ctrlNameCombo;
	afx_msg void OnBnClickedButtonCombo();
	CString m_strComboName;
};
