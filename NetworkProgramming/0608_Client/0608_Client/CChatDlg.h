#pragma once


// CChatDlg 대화 상자

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CChatDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COMMUNICATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()

public:
	void SendData(CString name);

private:
	CString m_name;
public:
	virtual BOOL OnInitDialog();
};
