
// ClientDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CClientDlg 对话框
CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
	, m_content(_T(""))
	, m_sendmsg(_T(""))
	, client_status(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTENT, m_recv);
	DDX_Control(pDX, IDC_MSG, m_send);
	DDX_Control(pDX, IDC_CONNECT, m_connect);
	DDX_Control(pDX, IDC_IP, m_ip);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_SENDMSG, &CClientDlg::OnBnClickedSendmsg)
	ON_BN_CLICKED(IDC_CLOSE, &CClientDlg::OnBnClickedClose)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	//套接字初始化
	Socketinit();
	//设置对话款标题为client + ip
	this->SetWindowText(CString("Client:") + GetLocalIP());
	//初始化ip地址控件
	m_ip.SetAddress(192, 168, 18, 128);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//初始化套接字函数
void CClientDlg::Socketinit()
{
	WSADATA wsa;
	//初始化WS2_32.DLL
	WSAStartup(MAKEWORD(2, 0), &wsa);
	//创建套接字
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		AfxMessageBox(_T("套接字socket创建失败!\n"));
		return ;
	}
	serveraddr.sin_family = AF_INET;
	//设置端口号
	serveraddr.sin_port = htons(6000);
}
//连接服务器按钮事件
void CClientDlg::OnBnClickedConnect()
{
	// TODO:  在此添加控件通知处理程序代码
	CString   strIP;
	//获得控件中的ip地址
	GetDlgItemText(IDC_IP, strIP);
	char ip[BUF_SIZE];
	cstring2char(strIP, ip);
	//将服务器ip设置为控件中的ip地址
	serveraddr.sin_addr.S_un.S_addr = inet_addr(ip);
	//打开连接客户端线程
	if (connect(clientsocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		AfxMessageBox(_T("连接失败！\n"));
		return;
	}
	//显示连接服务器进度条
	ProgressShow();
	//将连接按钮设置为不可用
	m_connect.EnableWindow(FALSE);
	//将客户端状态设置为打开
	client_status = true;
	//创建接受服务器数据线程
	m_Threadrecv = CreateThread(NULL, 0, ThreadProcRecv, this, 0, NULL);//创建新线程  
	//关闭线程句柄
	CloseHandle(m_Threadrecv);
}
//接受服务器消息线程函数
DWORD WINAPI ThreadProcRecv(LPVOID lpParam)
{
	CClientDlg *tmp = (CClientDlg *)lpParam;
	char buf[BUF_SIZE];
	mymsg::msg message;
	while (tmp->client_status)
	{
		memset(&buf, 0, BUF_SIZE);
		int retVal = recv(tmp->clientsocket, buf, BUF_SIZE, 0);
		if (retVal>0)
		{
			//将接受的protobuf协议反序列化
			message.ParseFromArray(buf, BUF_SIZE);
			tmp->m_content += message.data().c_str();
			tmp->m_recv.SetWindowText(tmp->m_content);
		}
	}
	return 0;
}

void CClientDlg::OnBnClickedSendmsg()
{
	// TODO:  在此添加控件通知处理程序代码
	mymsg::msg message;
	char temp[BUF_SIZE];
	memset(temp, 0, BUF_SIZE);
	if (client_status)
	{
		//获取发送编辑框中的字符串
		m_send.GetWindowText(m_sendmsg);
		//若消息为空，则不发送并提示
		if (m_sendmsg == "")
		{
			AfxMessageBox(_T("发送的消息不能为空！"));
			return;
		}
		cstring2char(m_sendmsg, temp);
		//设置发送的protobuf协议对象
		message.set_data(temp);
		message.set_type(mymsg::msg::SENDMSG);
		//将数据对象序列化
		message.SerializeToArray(temp, BUF_SIZE);
		if (send(clientsocket,temp, strlen(temp), 0) <= 0)
		{
			m_content += CString("发送错误!\r\n");
		}
		//发送成功后将发送编辑框清空并获得焦点以便下次发送
		m_sendmsg = "";
		m_send.SetWindowText(_T(""));
		m_send.SetFocus();
	}
}
//将CString多字节对象转化为char单字节对象函数
void CClientDlg::cstring2char(CString str, char c[])
{
	TCHAR wTmp[BUF_SIZE/2-1] = {};
	_tcscpy(wTmp, str.GetBuffer(0));
	int   nLen = wcslen(wTmp) + 1;
	WideCharToMultiByte(CP_ACP, 0, wTmp, nLen, c, 2 * nLen, NULL, NULL);
}
//关闭客户端按钮事件
void CClientDlg::OnBnClickedClose()
{
	// TODO:  在此添加控件通知处理程序代码
	mymsg::msg message;
	char temp[BUF_SIZE];
	if (client_status)
	{
		cstring2char(CString(" "), temp);
		//设置protobuf协议对象，消息类型为断开连接
		message.set_data(temp);
		message.set_type(mymsg::msg::DISCONNECT);
		//对数据进行序列化
		message.SerializeToArray(temp, BUF_SIZE);
		if (send(clientsocket, temp, strlen(temp), 0) <= 0)
		{
			m_content += CString(" 连接失败啦！\r\n");
		}
	}
	//将客户端状态设置为关闭
	client_status = false;
	//关闭客户端套接字
	closesocket(clientsocket);
	//释放WS2_32.DLL
	WSACleanup();
	CDialog::OnCancel();
}
//设置编辑框背景色函数
HBRUSH CClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_CONTENT)
	{ 
		COLORREF clr_bk = RGB(140, 200, 85);	//设置背景颜色  
		pDC->SetBkColor(clr_bk);
		m_brush = ::CreateSolidBrush(clr_bk);
		return m_brush;
	}
	else if (pWnd->GetDlgCtrlID() == IDC_MSG)
	{
		COLORREF clr_bk = RGB(160, 160, 230);	//设置背景颜色  
		pDC->SetBkColor(clr_bk);
		m_brush = ::CreateSolidBrush(clr_bk);
		return m_brush;
	}
	else
	{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		return hbr;
	}
}
CString CClientDlg::GetLocalIP()
{
	char szHostName[MAX_PATH + 1];
	gethostname(szHostName, MAX_PATH);			//得到计算机名
	hostent *p = gethostbyname(szHostName);		//从计算机名得到主机信息
	CString m_strName;
	m_strName = szHostName;						//保存主机名  
	int nCount = 0;								//保存主机地址
	//将32位IP转化为字符串IP
	char *pIP = inet_ntoa(*(in_addr *)p->h_addr_list[0]);  
	CString m_strAddr;
	m_strAddr = pIP;							//保存主机IP地址 
	return m_strAddr;
}
//显示进度条函数
void CClientDlg::ProgressShow()
{
	CProgressCtrl myProCtrl;
	CRect rect, proRect;
	//获得当前客户端大小
	GetClientRect(&rect);
	//设置进度条大小
	proRect.left = rect.left + rect.Width() / 2 - 100;
	proRect.top = rect.top + rect.Height() / 2 - 10;
	proRect.right = rect.right - rect.Width() / 2 + 100;
	proRect.bottom = rect.bottom - rect.Height() / 2 + 10;
	//创建位置、大小
	myProCtrl.Create(WS_VISIBLE, proRect, this, 99);
	myProCtrl.SetRange(0, 100);
	int i;
	for (i = 0; i < 100; i++)
	{
		myProCtrl.OffsetPos(1);
		Sleep(20);
	}
	return;
}