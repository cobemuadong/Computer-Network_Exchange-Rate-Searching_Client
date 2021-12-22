
// ClientDlg.h : header file
//

#ifndef CLIENTDLG_H
#define CLIENTDLG_H

// CClientDlg dialog
class CClientDlg : public CDialogEx
{
// Construction
public:
	CClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//To do:
	CEdit _edt_username;
	afx_msg void OnBnClickedLogin();
protected:
	CEdit _edt_password;
public:
	afx_msg void OnBnClickedRegister();
	CEdit _ip_address;

	bool InitialSocket(const char* ipAddress, int port, SOCKET& sock);
	SOCKET sClient = INVALID_SOCKET;
	afx_msg void OnBnClickedConnect();
	CEdit _edt_port;
	CButton _button_login;
	CButton _button_register;
	CButton _button_connect;
	int mSend(CString msg);
	CString mRecv();
	afx_msg void OnClose();

	afx_msg void OnEnChangeEdtUsername();
};

// your declarations here

#endif