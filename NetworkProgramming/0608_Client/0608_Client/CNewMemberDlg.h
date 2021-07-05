#pragma once


// CNewMemberDlg 대화 상자

class CNewMemberDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewMemberDlg)

public:
	CNewMemberDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNewMemberDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Join };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRealjoin();
	afx_msg void OnBnClickedButtonCheck();
	CString m_strID;
	CString m_strPassword;
	CString m_strName;
	void GetData(CString& ID, CString& PW, CString& Name);
};

