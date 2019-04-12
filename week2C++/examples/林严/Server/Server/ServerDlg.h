
// ServerDlg.h : 头文件
//

#pragma once
#include "msg.pb.h"
#include <stdio.h>
#include <winsock2.h>
#include <vector>
#include <string>
#include "afxwin.h"
#include <afxmt.h>
#include "afxcmn.h"
#include "afx.h"

#pragma comment(lib,"ws2_32.lib")
#define MAX_CLIENT_NUM 5				//客户端连接最大数量
#define BUF_SIZE 1024					//数据传输的buf大小
using namespace std;

//定义管理套接字对象的结构体
class MySocket
{
public:
	//重载==操作符用于find函数保存套接字
	bool operator==(const MySocket &S) const
	{ 
		if (this->ip == S.ip)
		{
			return true;
		}
		return false;
	 }
	SOCKET mysocket;					//套接字
	CString ip;							//套接字对应的ip
};
// CServerDlg 对话框
class CServerDlg : public CDialog
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void Socketinit();						//初始化套接字函数
	SOCKET server;							//服务器套接字对象
	SOCKADDR_IN serveraddr;					//服务器地址结构体对象
	SOCKADDR_IN clientaddr;					//客户端地址结构体对象
	HANDLE m_hThread[MAX_CLIENT_NUM];		//每个客户端数据传输线程句柄
	HANDLE m_startThread;					//服务器监听客户端线程句柄
	bool server_status;						//服务器状态标志
	HBRUSH m_brush;							//画刷
public:
	CString m_content;						//用于服务器与客户端之间数据内容的显示
	vector<MySocket> client;				//管理套接字容器
	CEdit m_text;							//显示消息的Edit控件对象
	MySocket *m_socket;						//开辟存放新连接套接字内存
	MySocket current_socket;				//当前连接套接字
	CButton m_start;						//启动服务器按钮控件
	CButton m_stop;							//关闭服务器按钮控件
	CRITICAL_SECTION m_clientlock;			//临界区对象用于线程的互斥
	CListCtrl m_list;						//列表对象用于显示当前客户端列表
	CTime current_time;						//获取系统时间对象
	CString mytime;							//获取系统时间字符串
	afx_msg void OnBnClickedStartserver();	//启动服务器按钮事件
	afx_msg void OnBnClickedStopserver();	//关闭服务器按钮事件
	//无参线程函数
	static unsigned __stdcall Thread(LPVOID lpParm)
	{
		((CServerDlg*)lpParm)->ThreadFun();
		return 0;
	}
	void ThreadFun(void);
	//发送消息给所有客户端的函数
	void sendtoall(mymsg::msg &message);
	//将CString多字节对象转为char单字节对象的函数
	void cstring2char(CString str, char c[]);
	//修改控件背景色函数
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//更新列表函数
	void CServerDlg::UpdateList();
};
DWORD WINAPI ThreadProc(LPVOID lpParam);	//服务器与客户端数据传输线程函数，全局函数