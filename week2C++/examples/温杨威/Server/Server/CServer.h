#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include "log_packet.pb.h"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#pragma comment(lib, "ws2_32.lib")
using namespace google::protobuf::io;
using namespace std;
#define IP_BUF_SIZE 129
typedef map<SOCKET,bool> ClIENTVECTOR;		//向量容器
class CServer
{
public:
	CServer();
	~CServer();
public:
	//等待客户端
	void WaitForClient();
	//数据包解析
	void static ReadMsg(SOCKET csock, google::protobuf::uint32 siz);
	void static SendData(SOCKET client, log_packet msg);
private:
	//存储被WSAStartup函数调用后返回的Windows Sockets数据
	WSADATA wsa_data;
	//定义server套接字
	SOCKET sock_server;
	//定义client套接字
	SOCKET sock_client;
	//定义句柄，创建线程
	HANDLE h_thread;
	//储存server地址和端口
	SOCKADDR_IN addr_server;
	//储存client地址和端口
	SOCKADDR_IN addr_client;
	//保存函数返回值，进行验证函数是否运行成功
	int rec_val;
	//保存地址长度
	int addr_len;
	//保存ip地址
	wchar_t buf_ip[IP_BUF_SIZE];
};

