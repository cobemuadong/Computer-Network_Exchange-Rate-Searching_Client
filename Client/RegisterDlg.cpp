// RegisterDlg.cpp : implementation file
//

#include "pch.h"
#include "Client.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "ClientDlg.h"


// RegisterDlg dialog

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER, pParent)
{

}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RG_USERNAME, _edt_rg_username);
	DDX_Control(pDX, IDC_RG_PASSWORD, _edt_rg_password);
	DDX_Control(pDX, IDC_RG_RE_PASSWORD, _edt_rg_re_password);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &RegisterDlg::OnBnClickedRegister)
END_MESSAGE_MAP()


// RegisterDlg message handlers

int	RegisterDlg::SendMsg(CString& msg)
{
	int len = msg.GetLength();
	char sendBuff[4096];
	ZeroMemory(sendBuff, 4096);
	strcpy_s(sendBuff, CStringA(msg).GetString());
	//Maybe send length?
	int BytesSent = send(sock, sendBuff, len, 0);
	if (BytesSent < 0)
		return 0;
	return 1;
}

int RegisterDlg::RecvMsg(char* msg)
{
	msg = new char[4096];
	int bytesReceived = recv(sock, msg, 4096, 0);
	delete[]msg;
	if (bytesReceived == SOCKET_ERROR)
		return 0;
	else
		return 1;
}

void RegisterDlg::OnBnClickedRegister()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString input_user;
	CString input_password;
	CString input_re_password;

	_edt_rg_username.GetWindowText(input_user);
	_edt_rg_password.GetWindowText(input_password);
	_edt_rg_re_password.GetWindowText(input_re_password);

	bool check = false;
	if (input_password.Compare(input_re_password) == 0)
	{
		check = true;
	}
	else
	{
		MessageBox(_T("Please check you Re-Password again!"), ERROR);
	}
	if (check == true)
	{
		//To do
		SendMsg(input_user);
		SendMsg(input_password);
		EndDialog(0);
	}
}
