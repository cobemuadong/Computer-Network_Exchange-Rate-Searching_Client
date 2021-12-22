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
	int BytesSent = send(sClient, sendBuff, len, 0);
	if (BytesSent < 0)
		return 0;
	return 1;
}

int RegisterDlg::mSend(CString msg)
{
	int wstr_len = (int)wcslen(msg);	//get length
	int num_chars = WideCharToMultiByte(CP_UTF8, 0, msg, wstr_len, NULL, 0, NULL, NULL);
	CHAR* strTo = new CHAR[num_chars + 1];
	if (strTo)
	{
		WideCharToMultiByte(CP_UTF8, 0, msg, wstr_len, strTo, num_chars, NULL, NULL);
		strTo[num_chars] = '\0';
	}
	int buffSent = send(sClient, (char*)&num_chars, sizeof(int), 0);
	if (buffSent <= 0)
		return 0;
	int bytesSent = send(sClient, strTo, num_chars, 0);
	if (bytesSent <= 0)
		return 0;
	return bytesSent;
}

int RegisterDlg::RecvMsg(char* msg)
{
	msg = new char[4096];
	int bytesReceived = recv(sClient, msg, 4096, 0);
	delete[]msg;
	if (bytesReceived == SOCKET_ERROR)
		return 0;
	else
		return 1;
}

CString RegisterDlg::mRecv()
{
	int buffLen;
	int buffReceived = recv(sClient, (char*)&buffLen, sizeof(int), 0);
	if (buffReceived < 0)
		return NULL;
	buffLen += 1;
	CHAR* temp = new CHAR[buffLen];
	ZeroMemory(temp, buffLen);
	int bytesReceived = recv(sClient, temp, buffLen, 0);
	if (bytesReceived < 0)
	{
		delete[]temp;
		return NULL;
	}
	else
	{
		int wchar_num = MultiByteToWideChar(CP_UTF8, 0, temp, strlen(temp), NULL, 0);
		if (wchar_num <= 0)
			return NULL;
		wchar_t* wstr = new wchar_t[wchar_num + 1];
		ZeroMemory(wstr, wchar_num);
		if (!wstr)
		{
			return NULL;
		}
		MultiByteToWideChar(CP_UTF8, 0, temp, strlen(temp), wstr, wchar_num);
		wstr[wchar_num] = '\0';
		CString X = wstr;
		delete[] wstr;
		delete[] temp;
		return X;
	}
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
		mSend(input_user);
		mSend(input_password);
		EndDialog(0);
	}
}
