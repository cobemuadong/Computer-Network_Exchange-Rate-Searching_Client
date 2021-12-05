
// ClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "RegisterDlg.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg dialog



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_USERNAME, _edt_username);
	DDX_Control(pDX, IDC_EDT_PASS, _edt_password);
	DDX_Control(pDX, IDC_IP, _ip_address);
	DDX_Control(pDX, IDC_EDT_PORT, _edt_port);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, &CClientDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_REGISTER, &CClientDlg::OnBnClickedRegister)
	ON_BN_CLICKED(IDC_CONNECT, &CClientDlg::OnBnClickedConnect)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_IP)->SetWindowTextW(_T("127.0.0.1"));
	GetDlgItem(IDC_EDT_PORT)->SetWindowTextW(_T("1234"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CClientDlg::InitialSocket(const char* ipAddress, int port)
{							// Listening port
	// Initialize winsock
	WSAData wsaData;
	WORD ver = MAKEWORD(2, 2);					//version 
	int wsResult = WSAStartup(ver, &wsaData);
	if (wsResult != 0)
	{
		MessageBox(_T("Can't star winsock, Err #%d", wsResult), 0, MB_ICONERROR);
		WSACleanup();
		return false;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		CString t;
		t.Format(_T("%d"), WSAGetLastError());
		MessageBox(_T("Can't create socket, Err #") + t, 0, MB_ICONERROR);
		WSACleanup();
		return false;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;			// TCP
	hint.sin_port = htons(port);
	int iResult = inet_pton(AF_INET, ipAddress, &hint.sin_addr);
	if (iResult == -1 || iResult == 0)// Convert string to IP Address
	{
		MessageBox(_T("Wrong IP!!!"), 0, MB_ICONERROR);
		return false;
	}

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		CString t;
		t.Format(_T("%d"), WSAGetLastError());
		MessageBox(_T("Can't connect to server, Err #") + t, 0, MB_ICONERROR);
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// Do-while loop to send and receive data

	// Gracefully close down everything
	
	//closesocket(sock);
	//WSACleanup();

	return true;
}

void CClientDlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	CString user_str;
	CString pass_str;

	CString input_name;
	CString input_pass;

	_edt_username.GetWindowText(input_name);
	_edt_password.GetWindowText(input_pass);

	bool is_login = false;
	if (input_name.CompareNoCase(user_str) == 0)
	{
		if (input_pass.Compare(pass_str) == 0)
		{
			is_login = true;
		}
	}

	if (is_login)
	{
		//MainDlg main_dlg;
		//main_dlg.DoModal();
	}
}


void CClientDlg::OnBnClickedRegister()
{
	// TODO: Add your control notification handler code here
	RegisterDlg rgt;
	rgt.DoModal();

}


void CClientDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//Connect to socket
	CString ip_temp;
	CString port_temp;
	_ip_address.GetWindowText(ip_temp);
	_edt_port.GetWindowText(port_temp);
	//Convert to tchar
	/*TCHAR* IP = new TCHAR[temp.GetLength() + 1];
	_tcscpy_s(IP, temp.GetLength() + 1, temp);*/
	
	// Convert to char*
	CStringA temp(ip_temp);
	const char* ip = temp;

	// Convert to int
	int port = _tstoi(port_temp);

	if (InitialSocket(ip, port))
	{
		if (sock == INVALID_SOCKET)
		{
			MessageBox(_T("deo on!"));
		}
		else
		{
			MainDlg main;
			main.sock = sock;
			theApp.m_pMainWnd = &main;
			EndDialog(IDOK);
			main.DoModal();
		}
	}
}
