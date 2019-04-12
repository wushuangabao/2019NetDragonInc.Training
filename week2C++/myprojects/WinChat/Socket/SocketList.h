#ifndef SOCKETLIST_H
#define SOCKETLIST_H

#include "TCPSocket.h"
#include "data.pb.h"
#include <list>
#include <vector>
using namespace std;
class SocketList
{
public:
	SocketList(bool IsServer, string ConnectIp = "127.0.0.1");//创建服务器/客户端
	~SocketList();
	void Send(string str);//发送信息
	list<string> Listening(DataSocket **RecSocket = NULL);//监听有无消息
private:
	void SendToAllClient(list<string> StrList);//以字符串链表发送到所有客户端
	void SendToAllClient(string str);//以一个字符串发送到所有客户端
	void SendToServer(string str);//以一个字符串发送到服务器
	list<DataSocket*> SerDatSockList;//服务器用来保存每个与客户端通信的数据套接字
	fd_set rset;//套接字集，用来保存待监听的套接字
	struct timeval zerotime;//填充结构体表示立即返回
	BaseSocket *ConnectSocket;//创建/连接的时候用的套接字
	bool isServer;//是否为服务器
};

#endif
