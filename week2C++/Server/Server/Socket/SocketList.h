#ifndef SOCKETLIST_H
#define SOCKETLIST_H

#include "TCPSocket.h"
#include <list>

class Chat;

using namespace std;
class SocketList
{
public:
	SocketList(bool IsServer, string ConnectIp = "127.0.0.1");
	~SocketList();
	list<string> Listening(Chat* chat,DataSocket **RecSocket = NULL);  //监听有无消息
	void SendToAllClient(string str);          //广播一个字符串

private:
	list<DataSocket*> SerDatSockList;//保存所有与客户端通信的数据套接字
	fd_set rset;                     //套接字集，保存待监听的套接字
	struct timeval zerotime;         //used in select() call
	BaseSocket *ConnectSocket;
	void SendToAllClient(list<string> StrList); //广播字符串链表
};

#endif
