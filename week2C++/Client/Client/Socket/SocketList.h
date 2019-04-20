#ifndef SOCKETLIST_H
#define SOCKETLIST_H

#include "TCPSocket.h"
#include <list>
#include <vector>
using namespace std;
class SocketList
{
public:
	SocketList(string ConnectIp = "127.0.0.1");
	~SocketList();
	void SendToServer(string str);              //发送一个字符串到服务器
	list<string> Listening();//监听有无消息

private:
	//list<DataSocket*> SerDatSockList;//服务器用来保存每个与客户端通信的数据套接字
	fd_set rset;              //套接字集，用来保存待监听的套接字
	struct timeval zerotime;  //used in select() call
	BaseSocket *ConnectSocket;
};

#endif
