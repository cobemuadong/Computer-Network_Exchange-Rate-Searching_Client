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

int RegisterDlg::mSend(CString msg)
{
	int wstr_len = (int)wcslen(msg);	//get length
	int num_chars = WideCharToMultiByte(CP_UTF8, 0, msg, wstr_len, NULL, 0, NULL, NULL);
	char* strTo = new char[num_chars + 1];
	ZeroMemory(strTo, num_chars + 1);
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

int RegisterDlg::mRecv(CString& StrRecv)
{
	int buffLen;
	int buffReceived = recv(sClient, (char*)&buffLen, sizeof(int), 0);
	if (buffReceived < 0)
		return SOCKET_ERROR;
	char* temp = new char[buffLen + 1];
	ZeroMemory(temp, buffLen);
	int bytesReceived = recv(sClient, temp, buffLen, 0);
	temp[buffLen] = '\0';
	if (bytesReceived < 0)
	{
		delete[]temp;
		return SOCKET_ERROR;
	}
	else
	{
		int wchar_num = MultiByteToWideChar(CP_UTF8, 0, temp, strlen(temp), NULL, 0);
		if (wchar_num <= 0)
			return -1;
		wchar_t* wstr = new wchar_t[wchar_num + 1];
		ZeroMemory(wstr, wchar_num);
		if (!wstr)
		{
			return -1;
		}
		MultiByteToWideChar(CP_UTF8, 0, temp, strlen(temp), wstr, wchar_num);
		wstr[wchar_num] = '\0';
		StrRecv = wstr;
		delete[] wstr;
		delete[] temp;
		return bytesReceived;
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

	mSend(_T("1"));

	bool check = false;
	if (input_password.Compare(input_re_password) == 0)
	{
		mSend(input_user);
		mSend(input_password);
		CString isRegis;
		mRecv(isRegis);
		if (isRegis.Compare(_T("1")) == 0)
		{
			MessageBox(_T("Đăng ký thành công!"));
			EndDialog(0);
		}
		else
		{
			MessageBox(_T("Username đã tồn tại"));
		}
	}
	else
	{
		MessageBox(_T("Please check you Re-Password again!"), ERROR);
	}
}
