#pragma once


// RegisterDlg dialog

class RegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RegisterDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CEdit _edt_rg_username;
	CEdit _edt_rg_password;
	CEdit _edt_rg_re_password;
public:
	afx_msg void OnBnClickedRegister();
	SOCKET sClient;
	int mSend(CString msg);
	int mRecv(CString&StrRecv);

};
