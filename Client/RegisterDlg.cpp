// RegisterDlg.cpp : implementation file
//

#include "pch.h"
#include "Client.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"


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
	ON_BN_CLICKED(IDC_BUTTON1, &RegisterDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// RegisterDlg message handlers


void RegisterDlg::OnBnClickedButton1()
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
		EndDialog(0);
	}
}
