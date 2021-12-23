// MainDlg.cpp : implementation file
//

#include "pch.h"
#include "Client.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// MainDlg dialog

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINDLG, pParent)
{

}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL, _list_ctrl_output);
	DDX_Control(pDX, IDC_COMBO1, _combox1);
	DDX_Control(pDX, IDC_COMBO2, _combox2);
	DDX_Control(pDX, IDC_COMBO3, _combox3);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, _button_search);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, _datetimepicker);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &MainDlg::OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO1, &MainDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// MainDlg message handlers

void setOptionCombox(CComboBox* _combox, vector<CString> VecA)
{
	for (int i = 0; i < VecA.size(); i++)
	{
		_combox->AddString(VecA[i]);
	}
}

BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization hereconst int iFontSize = 25;
	const int iFontSize = 23;
	const CString sFont = _T("Segoe UI");
	HFONT hFont = CreateFontW(iFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, sFont);
	_list_ctrl_output.SendMessageW(WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);


	CRect rect;
	CWnd* pWnd = this->GetDlgItem(IDC_LISTCTRL);
	pWnd->GetWindowRect(&rect);
	this->ScreenToClient(&rect);
	int width = rect.Width() / 5;

	_list_ctrl_output.InsertColumn(0, _T("Bán ra"), LVCFMT_LEFT, width);
	_list_ctrl_output.InsertColumn(0, _T("Mua vào"), LVCFMT_LEFT, width);
	_list_ctrl_output.InsertColumn(0, _T("Hãng"), LVCFMT_LEFT, width);
	_list_ctrl_output.InsertColumn(0, _T("Loại"), LVCFMT_LEFT, width + 40);
	_list_ctrl_output.InsertColumn(0, _T("Công ty"), LVCFMT_LEFT, width - 40);

	_combox1.SendMessageW(WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	_combox2.SendMessageW(WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	_combox3.SendMessageW(WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	_datetimepicker.SendMessageW(WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);

	_datetimepicker.SetFormat(_T("dd/MM/yyyy"));

	GetDlgItem(IDC_COMBO1)->SetWindowTextW(_T("Công ty"));
	GetDlgItem(IDC_COMBO2)->SetWindowTextW(_T("Loại"));
	GetDlgItem(IDC_COMBO3)->SetWindowTextW(_T("Thương hiệu"));

	vector<CString> company = { _T("SJC"),_T("DOJI"),_T("3BANKS"),_T("2GROUP"),_T("1OTHER"),_T("1Coin"),_T("Tất cả") };
	vector<CString>type = { _T("Vàng SJC"),_T("Vàng SJC 1L"),_T("Vàng nhẫn SJC 99,99 0,5 chỉ"),
		_T("Vàng nhẫn SJC 99,99 1 chỉ, 2 chỉ, 5 chỉ"),_T("Vàng nữ trang 99,99%"),_T("Vàng nữ trang 99%"),
		_T("Vàng nữ trang 75%"),_T("Vàng nữ trang 58,3%"),_T("Vàng nữ trang 41,7%"),_T("AVPL / DOJI HCM buôn"),
		_T("AVPL / DOJI HCM lẻ"),_T("AVPL / DOJI CT buôn"),_T("AVPL / DOJI CT lẻ"),_T("AVPL / DOJI ĐN buôn"),
		_T("AVPL / DOJI ĐN lẻ"),_T("AVPL / DOJI HN buôn"),_T("AVPL / DOJI HN lẻ"),_T("Nguyên liêu 9999 - HN"),
		_T("Nguyên liêu 999 - HN"),_T("Kim Ngưu"),_T("Kim Thần Tài"),_T("Lộc Phát Tài"),_T("Kim Ngân Tài"),
		_T("Hưng Thịnh Vượng"),_T("Nhẫn H.T.V"),_T("Nguyên liệu 99.99"),_T("Nguyên liệu 9999"),_T("Nguyên liệu 99.9"),
		_T("Nguyên liệu 999"),_T("Nữ trang 99.99"),_T("Nữ trang 99.9"),_T("Nữ trang 99"),_T("Nữ trang 18k"),
		_T("Nữ Trang 18k"),_T("Nữ trang 16k"),_T("Nữ trang 68"),_T("Nữ trang 14k"),_T("Nữ Trang 14k"),
		_T("Nữ trang 10k"),_T("SJC"),_T("SJC*"),_T("Tất cả") };
	vector<CString> brand = { _T("Long Xuyên"),_T("Bạc Liêu"),_T("Biên Hòa"),_T("Cà Mau"),
		_T("Hà Nội"),_T("Hồ Chí Minh"),_T("Miền Tây"),_T("Nha Trang"),_T("Quãng Ngãi"),
		_T("Đà  Nẵng"),_T("Bình Phước"),_T("Hạ Long"),_T("Phan Rang"),_T("Quảng Nam"),
		_T("Quy Nhơn"),_T("Huế"),_T("Nhẫn DOJI Hưng Thịnh Vượng"),_T("MARITIME BANK"),
		_T("SACOMBANK"),_T("Mi Hồng SJC"),_T("PHÚ QUÝ SJC"),_T("Ngọc Hải SJC HCM"),
		_T("Ngọc Hải SJC Long An"),_T("Ngọc Hải SJC Tân Hiệp"),_T("SPOT GOLD"),
		_T("OIL"),_T("Nhẫn PHÚ QUÝ 24K"),_T("Nhẫn SJC 99,99"),_T("Mi Hồng 999"),
		_T("Ngọc Hải 24K HCM"),_T("Ngọc Hải 24K Long An"),_T("Ngọc Hải 24K Tân Hiệp"),
		_T("Mi Hồng 985"),_T("Mi Hồng 980"),_T("Ngọc Hải 17K HCM"),_T("Ngọc Hải 17K Long An"),
		_T("Ngọc Hải 17K Tân Hiệp"),_T("Mi Hồng 750"),_T("Mi Hồng 680"),_T("Mi Hồng 610"),_T("Mi Hồng 950"),_T("Tất cả") };

	setOptionCombox(&_combox1, company);
	setOptionCombox(&_combox2, type);
	setOptionCombox(&_combox3, brand);

	HFONT textFont = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, sFont);
	_button_search.SendMessageW(WM_SETFONT, reinterpret_cast<WPARAM>(textFont), TRUE);

	_button_search.SetButtonStyle(BS_DEFPUSHBUTTON);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

int mSend(SOCKET& sClient, CString msg)
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

int mRecv(SOCKET& sClient, CString& StrRecv)
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

void MainDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	shutdown(sClient, 0);
	closesocket(sClient);
	CDialogEx::OnClose();
}

UINT GetData(LPVOID param)
{
	MainDlg* ptr = (MainDlg*)param;
	CString num;
	//mRecv(ptr->sClient, num);
	size_t n = _tstoll(num);
	CString mr_company;
	CString mr_type;
	CString mr_brand;
	CString mr_buy;
	CString mr_sell;
	while (true)
	{
		mRecv(ptr->sClient, num);
		if (num.Compare(_T("1")) != 0)
			break;

		mRecv(ptr->sClient, mr_company);
		mRecv(ptr->sClient, mr_type);
		mRecv(ptr->sClient, mr_brand);
		mRecv(ptr->sClient, mr_buy);
		mRecv(ptr->sClient, mr_sell);
		ptr->_list_ctrl_output.InsertItem(0, mr_company);
		ptr->_list_ctrl_output.InsertItem(1, mr_type);
		ptr->_list_ctrl_output.InsertItem(2, mr_brand);
		ptr->_list_ctrl_output.InsertItem(3, mr_buy);
		ptr->_list_ctrl_output.InsertItem(4, mr_sell);
	}
	return 0;
}

void MainDlg::OnBnClickedButtonSearch()
{
	// TODO: Add your control notification handler code here
	mSend(sClient, _T("2"));
	CString ms_company;
	CString ms_type;
	CString ms_brand;
	_combox1.GetWindowTextW(ms_company);
	_combox2.GetWindowTextW(ms_type);
	_combox3.GetWindowTextW(ms_brand);

	CTime timeTime;
	DWORD dwResult = _datetimepicker.GetTime(timeTime);
	CString ms_date;
	if (dwResult == GDT_VALID)
	{
		// is it a time-only control, or a date-only control?
		if ((_datetimepicker.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
			ms_date = timeTime.Format(_T("%X")); //time hh-mm-ss
		else
			ms_date = timeTime.Format(_T("%Y%m%d")); //day mm-dd-yy
	}
	else
		AfxMessageBox(_T("Time not set!"));

	if (mSend(sClient, ms_company) == 0 || mSend(sClient, ms_type) == 0 || mSend(sClient, ms_brand) == 0 || mSend(sClient, ms_date) == 0)
	{
		MessageBox(_T("Không gửi được\nVui lòng thử lại!"));
		return;
	}
	/*CString num;
	mRecv(sClient, num);
	size_t n = _tstoll(num);
	CString mr_company;
	CString mr_type;
	CString mr_brand;
	CString mr_buy;
	CString mr_sell;
	for (size_t i = 0; i < n; i++)
	{
		mRecv(sClient, mr_company);
		mRecv(sClient, mr_type);
		mRecv(sClient, mr_brand);
		mRecv(sClient, mr_buy);
		mRecv(sClient, mr_sell);
		_list_ctrl_output.InsertItem(0, mr_company);
		_list_ctrl_output.InsertItem(1, mr_type);
		_list_ctrl_output.InsertItem(2, mr_brand);
		_list_ctrl_output.InsertItem(3, mr_buy);
		_list_ctrl_output.InsertItem(4, mr_sell);
		_list_ctrl_output.InsertItem(5, mr_company);
	}*/
	CWinThread* thread = AfxBeginThread(GetData, this);
}


void MainDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}
