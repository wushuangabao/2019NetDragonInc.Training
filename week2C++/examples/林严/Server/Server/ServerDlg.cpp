
// ServerDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CServerDlg 对话框
CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
	, m_content(_T("")), server_status(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTENT, m_text);
	DDX_Control(pDX, IDC_STARTSERVER, m_start);
	DDX_Control(pDX, IDC_STOPSERVER, m_stop);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTSERVER, &CServerDlg::OnBnClickedStartserver)
	ON_BN_CLICKED(IDC_STOPSERVER, &CServerDlg::OnBnClickedStopserver)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//对按钮显示进行初始化，打开服务器按钮可用，关闭服务器按钮不可用
	m_start.EnableWindow(!server_status);
	m_stop.EnableWindow(server_status);
	//初始化套接字
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	Socketinit();

	CRect rect;
	// 获取列表视图控件的位置和大小   
	m_list.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加一列   
	m_list.InsertColumn(0, _T("IP地址"), LVCFMT_CENTER, rect.Width() , 0);
	//初始化临界区对象
	InitializeCriticalSection(&m_clientlock);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//socket初始化函数
void CServerDlg::Socketinit()
{
	WSADATA wsa;
	//初始化WS2_32.DLL
	WSAStartup(MAKEWORD(2, 0), &wsa);
	//创建套接字
	if ((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		AfxMessageBox(_T("套接字socket创建失败!"));
		return ;
	}
	//设置套接字非阻塞模式
	unsigned long ul = 1;
	int reVal = ioctlsocket(server, FIONBIO, (unsigned long*)&ul);
	if (SOCKET_ERROR == reVal)
		return;
	//命名协议，IP，端口
	serveraddr.sin_family = AF_INET;
	//设置监听端口为6000
	serveraddr.sin_port = htons(6000);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//绑定套接字
	if (bind(server, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		AfxMessageBox(_T("套接字绑定失败!"));
		return ;
	}
}
//打开服务器按钮事件
void CServerDlg::OnBnClickedStartserver()
{
	// TODO:  在此添加控件通知处理程序代码
	//监听客户的连接
	int retVal = listen(server, MAX_CLIENT_NUM);
	if (SOCKET_ERROR == retVal)
	{
		AfxMessageBox(_T("监听失败!"));
		return ;
	}
	//服务器状态修改为打开
	server_status = true;
	//打开服务器按钮不可用，关闭服务器按钮可用
	m_start.EnableWindow(!server_status);
	m_stop.EnableWindow(server_status);
	//打开连接客户端线程
	m_startThread = (HANDLE)_beginthreadex(0, 0, Thread, this, 0, NULL);
}
//关闭服务器按钮事件
void CServerDlg::OnBnClickedStopserver()
{
	// TODO:  在此添加控件通知处理程序代码
	//服务器状态修改为关闭
	server_status = false;
	//打开服务器按钮可用，关闭服务器按钮不可用
	m_start.EnableWindow(!server_status);
	m_stop.EnableWindow(server_status);
	//释放线程句柄
	CloseHandle(m_startThread);
	//清空客户端管理容器
	if (!client.empty())
	{
		client.clear();
	}
	//释放WS2_32.DLL
	WSACleanup();
	CDialog::OnCancel();
}
//监听客户端连接线程
void CServerDlg::ThreadFun()
{
	SOCKET clientsoc;												//定义临时套接字变量
	int len;
	len = sizeof(SOCKADDR_IN);
	struct sockaddr_in sa;
	int i = 0;
	while (server_status)
	{
		memset(&sa, 0, sizeof(sockaddr_in));						//初始化
		clientsoc = accept(server, (sockaddr*)&clientaddr, &len);	//接受客户请求
		if (INVALID_SOCKET == clientsoc)
		{
			int nErrCode = WSAGetLastError();
			if (nErrCode == WSAEWOULDBLOCK)							//无法立即完成一个非阻挡性套接字操作
			{
				Sleep(500);											//线程等待时间500ms
				continue;											//继续等待
			}
			else
			{
				return ;											//线程退出
			}

		}
		//接受客户端的请求
		else
		{
			getpeername(clientsoc, (struct sockaddr *)&sa, &len);	//获得客户端ip地址
			m_socket = new MySocket();								//分配内存
			m_socket->mysocket = clientsoc;
			m_socket->ip = CString(inet_ntoa(sa.sin_addr));
			current_socket = *m_socket;
			EnterCriticalSection(&m_clientlock);
			client.push_back(*m_socket);							//将新连接的客户端放入管理容器中
			UpdateList();											//更新列表
			LeaveCriticalSection(&m_clientlock);
			current_time = CTime::GetCurrentTime();
			mytime = current_time.Format("%Y年%m月%d日%X\r\n");
			m_content += mytime;									//添加当前时间
			m_content += m_socket->ip;
			m_content += " 连接上服务器啦！\r\n";
			m_text.SetWindowText(m_content);						//显示客户端已连接消息
			mymsg::msg connectmsg;									//protobuf协议封装数据
			char temp[BUF_SIZE];
			cstring2char((mytime + m_socket->ip + CString(" 连接上服务器啦！\r\n")), temp);
			connectmsg.set_type(mymsg::msg::SENDMSG);				//设置消息类型
			connectmsg.set_data(temp);								//设置消息内容
			sendtoall(connectmsg);									//调用广播函数
			//开启一个接收数据线程
			m_hThread[i++] = CreateThread(NULL, 0, ThreadProc, this, 0, NULL);//创建新线程  
			CloseHandle(m_hThread[i - 1]);							//释放线程句柄
		}

	}
}
//服务器与客户端数据传输线程
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	CServerDlg *tmp = (CServerDlg *)lpParam;						
	MySocket mstmp = tmp->current_socket;							//得到当前连接的客户端对象
	SOCKET clienttmp = mstmp.mysocket;
	char buf[BUF_SIZE];
	mymsg::msg message;
	while (true)
	{
		memset(&buf, 0, BUF_SIZE);
		int retVal = recv(clienttmp, buf, BUF_SIZE , 0);			//接收客户端发送的消息
		if (retVal>0)
		{
			message.ParseFromArray(buf, BUF_SIZE);					//对象接收的protobuf协议进行反序列化
			//如果消息是发送给另一个客户端的话，则服务将消息发送给另一个客户端
			if (message.type() == mymsg::msg::SENDMSG)
			{
				tmp->current_time = CTime::GetCurrentTime();
				tmp->mytime = tmp->current_time.Format("%Y年%m月%d日%X\r\n");
				//字符串拼接，时间 + ip + 说 + 消息内容
				tmp->m_content = tmp->m_content + tmp->mytime + CString(mstmp.ip) + CString(" 说：") + message.data().c_str() + CString("\r\n");
				tmp->m_text.SetWindowText(tmp->m_content);
				//调用广播函数发送消息
				CString str = (tmp->mytime + CString(mstmp.ip) + CString(" 说：") + message.data().c_str() + CString("\r\n"));
				char temp[BUF_SIZE];
				tmp->cstring2char(str, temp);
				//封装protobuf协议传输数据
				message.set_data(temp);
				message.set_type(mymsg::msg::SENDMSG);
				//调用广播函数
				tmp->sendtoall(message);
			}
			//如果消息是客户端关闭了，则关闭当前线程
			if (message.type() == mymsg::msg::DISCONNECT)
			{
				//关闭套接字
				closesocket(clienttmp);
				//寻找当前关闭客户端对象的迭代器对象
				vector<MySocket>::iterator itr = find(tmp->client.begin(), tmp->client.end(), mstmp);
				//客户端容器是线程共享资源，所以需要进入临界区
				EnterCriticalSection(&tmp->m_clientlock);
				//删除当前客户端的套接字对象
				tmp->client.erase(itr);
				tmp->UpdateList();
				//离开临界区
				LeaveCriticalSection(&tmp->m_clientlock);
				//字符串拼接，时间 + ip + 断开连接
				tmp->current_time = CTime::GetCurrentTime();
				tmp->mytime = tmp->current_time.Format("%Y年%m月%d日%X\r\n");
				tmp->m_content = tmp->m_content + tmp->mytime + CString(mstmp.ip) + CString(" 断开连接啦！\r\n");
				tmp->m_text.SetWindowText(tmp->m_content);
				char temp[BUF_SIZE];
				tmp->cstring2char(tmp->mytime + CString(mstmp.ip) + CString(" 断开连接啦！\r\n"), temp);
				//封装protobuf协议对象
				message.set_data(temp);
				message.set_type(mymsg::msg::SENDMSG);
				tmp->sendtoall(message);
				break;
			}
		}
	}
	return 0;
}
//广播函数
void CServerDlg::sendtoall(mymsg::msg &message)
{
	char temp[BUF_SIZE];
	memset(temp, 0, BUF_SIZE);
	//进入操作客户端容器的临界区
	EnterCriticalSection(&m_clientlock);
	for (int i = 0; i < client.size();i++)
	{
		//对protobuf协议的对象进行序列化
		message.SerializeToArray(temp, BUF_SIZE);
		if (send(client[i].mysocket, temp, strlen(temp), 0) <= 0)
		{
			AfxMessageBox(_T("发送错误!"));
		}
	}
	//离开临界区
	LeaveCriticalSection(&m_clientlock);
}
//将CString多字节对象转为char单字节对象的函数
void CServerDlg::cstring2char(CString str, char* c)
{
	TCHAR wTmp[BUF_SIZE / 2 - 1] = {};
	_tcscpy(wTmp, str.GetBuffer(0));
	int   nLen = wcslen(wTmp) + 1;
	WideCharToMultiByte(CP_ACP, 0, wTmp, nLen, c, 2 * nLen, NULL, NULL);
}
//修改背景颜色函数
HBRUSH CServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_CONTENT)
	{
		COLORREF clr_bk = RGB(140, 200, 85);	//此处设置背景颜色  
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
//更新在线客户端列表
void CServerDlg::UpdateList()
{
	//先清空列表，在添加当前在线客户端
	m_list.DeleteAllItems();
	for (int i = 0; i < client.size(); i++)
	{
		m_list.InsertItem(i, client[i].ip);
	}
	UpdateWindow();
}