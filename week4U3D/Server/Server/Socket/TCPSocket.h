#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Platform.h"
#include <string>
#include <Windows.h>

class BaseSocket
{
	friend class SocketList;
public:
	virtual ~BaseSocket();
	int GetSocket();
  //int room = 0;              //房间号
	std::string userName = ""; //用户名
protected:
	int sock;
	const int port;
	struct sockaddr_in socketaddress;
	BaseSocket(int PassSocket = -1);
private:
	void CreateSock();
	void CloseSock();
};

class DataSocket : public BaseSocket
{
public:
	DataSocket(int PassSocket = -1);
	int SendData(std::string str);         //发送数据
	std::string ReceiveData();             //接收数据
};

class ListenSocket : public BaseSocket
{
public:
	ListenSocket();
	DataSocket* AcceptConnect();//接受连接
private:
	void BindSocket(); //绑定Socket
	void Listening();  //监听有无请求连接
};

#endif