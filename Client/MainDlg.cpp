// MainDlg.cpp : implementation file
//
#pragma once

#include "pch.h"
#include "Client.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "ClientDlg.h"

// MainDlg dialog

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN, pParent)
{

}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, _list_msg);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SEND, &MainDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// MainDlg message handlers


void MainDlg::received()
{
	// TODO: Add your control notification handler code here
	char buf[4096];
	ZeroMemory(buf, 4096);					// Fills the block of memory by zero
	int byteReceived = recv(sock, buf, 4096, 0);
	if (byteReceived > 0)
	{
		//Echo reponse to console
		//print the msg
		_list_msg.AddString(_T("Message received!!"));
	}
}

void MainDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	if (sock == INVALID_SOCKET)
	{
		CString t;
		t.Format(_T("%d"), WSAGetLastError());
		_list_msg.AddString(t);
	}
	else
	{
		char a[4] = "hi";
		int iResult = send(sock, a, 4, 0);
		if (iResult > 0)
		{
			_list_msg.AddString(_T("ok"));
		}
	}
	/*char buf[4096];
	char a[4] = "hi";
	int result = send(sock, a, 4, 0);
	if (result == SOCKET_ERROR) {
		if (sock == INVALID_SOCKET)
		{
			_list_msg.AddString(_T("deo on"));
		}
		CString t;
		t.Format(_T("%d"), WSAGetLastError());
		_list_msg.AddString(t);
	}*/
	//ZeroMemory(buf, 4096);					// Fills the block of memory by zero
	//int bytesReceived = recv(sock, buf, 4096, 0);
	//if (bytesReceived > 0)
	//{
	//	//Echo reponse to console
	//}
	//if (bytesReceived != SOCKET_ERROR)
	//{
	//	_list_msg.AddString(_T("di ngu!"));
	//}
	//else
	//{
	//	if (bytesReceived != 0)
	//	{
	//		_list_msg.AddString(_T("message received!"));
	//	}
	//}
}
