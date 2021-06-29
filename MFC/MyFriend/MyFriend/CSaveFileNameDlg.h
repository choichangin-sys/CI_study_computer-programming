#pragma once


// CSaveFileNameDlg 대화 상자

class CSaveFileNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveFileNameDlg)

public:
	CSaveFileNameDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSaveFileNameDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVENAMEFILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSavename();
};
