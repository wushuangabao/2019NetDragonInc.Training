
// ClientDlg.h : 头文件
//
#pragma once
#include <stdio.h>
#include <winsock2.h>
#include <string>
#include "afxwin.h"
#include "msg.pb.h"
#include "afxcmn.h"

#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 1024					//数据传输缓存区大小
using namespace std;

// CClientDlg 对话框
class CClientDlg : public CDialog
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	HBRUSH m_brush;						//修改背景色画刷
	void Socketinit();					//套接字初始化函数
	CString GetLocalIP();				//获得本地IP函数
public:
	SOCKET clientsocket;				//客户端套接字对象
	SOCKADDR_IN serveraddr;				//服务器地址结构体对象
	SOCKADDR_IN clientaddr;				//客户端地址结构体对象
	CString m_content;					//内容显示字符串
	CString m_sendmsg;					//发送内容字符串
	afx_msg void OnBnClickedConnect();	//连接服务器按钮事件
	HANDLE m_Threadrecv;				//接受数据线程句柄
	bool client_status;					//客户端状态标志
	afx_msg void OnBnClickedSendmsg();	//发送消息按钮事件
	afx_msg void OnBnClickedClose();	//客户端关闭按钮事件
	//将CString多字节对象转化为char单字节对象函数
	void cstring2char(CString str, char c[]);
	CEdit m_recv;						//接受编辑框对象
	CEdit m_send;						//发送编辑框对象
	//改变背景色函数
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_connect;					//连接按钮对象
	void ProgressShow();				//显示进度条函数
	CIPAddressCtrl m_ip;				//IP地址编辑框对象
};
DWORD WINAPI ThreadProcRecv(LPVOID lpParam);//接收数据线程函数，全局函数