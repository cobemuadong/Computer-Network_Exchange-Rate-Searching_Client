#pragma once
#include <vector>

// MainDlg dialog

class MainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl _list_ctrl_output;
	afx_msg void OnClose();
	
public: 
	SOCKET sClient = INVALID_SOCKET;
	WSAData wsaData;
	sockaddr_in hint;
	CComboBox _combox1;
	CComboBox _combox2;
	CComboBox _combox3;
	CButton _button_search;
	afx_msg void OnBnClickedButtonSearch();
	CDateTimeCtrl _datetimepicker;
	afx_msg void OnCbnSelchangeCombo1();
	CStatic _static1;
	CStatic _static2;
	CStatic _static3;
};
