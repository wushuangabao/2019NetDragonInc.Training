#pragma once
#include "CSocketBase.h"
#include "../msgManger/CMsgManger.h"
class CTcpServer: public CSocketBase
{
public:
	CTcpServer();
	CTcpServer(char *ip, unsigned short port);
	void Bind();
	void Listen();
	SOCKET Accept();
	//开始listen客户端
	void clientListen();
	//监听客户端，并根据select进行相应处理
	void Recv();
protected:
	CMsgManger *m_msgManger;
};