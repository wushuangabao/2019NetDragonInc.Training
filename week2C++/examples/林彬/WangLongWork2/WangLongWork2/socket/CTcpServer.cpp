#include<iostream>
using namespace std;
#include "CTcpServer.h"
#include "../msgManger/commun.pb.h"

CTcpServer::CTcpServer()
{
	m_msgManger = CMsgManger::getSingleton();
}
CTcpServer::CTcpServer(char * ip, unsigned short port)
	:CSocketBase(ip, port)
{
	m_msgManger = CMsgManger::getSingleton();
}
void CTcpServer::Bind()
{
	if (SOCKET_ERROR == ::bind(m_socket, addr.getPtr(), addr.getSize()))
	{
		Close();
		perror("bind");
		exit(0);
	}
}
void CTcpServer::Listen()
{
	if(listen(m_socket, 10) == SOCKET_ERROR)
	{
		Close();
		perror("listen");
		exit(0);
	}
}
SOCKET CTcpServer::Accept()
{	
	SOCKET client_fd;
	client_fd = accept(m_socket, addr.getPtr(), addr.getSizePtr());
	if(client_fd == INVALID_SOCKET)
	{
		perror("accept");
		Close();
		exit(0);
	}
	else 
	{
		return client_fd;
	}
}
void CTcpServer::clientListen()
{
	Socket(SOCK_STREAM);
	Bind();
	Listen();
	FD_SET(m_socket, &m_fdRead);
}

void CTcpServer::Recv()
{
	int handleNum;
	int ret;
	int count;
	SOCKADDR_IN addrClient;
	timeval tv;
	tv.tv_sec = 1;
	int size = sizeof(SOCKADDR_IN);
	char readBuf[BUFFERSIZE] = { 0 };

	while (1)
	{
		FD_ZERO(&m_fdTempRead);
		m_fdTempRead = m_fdRead;//事件集赋值，并非简单的指针赋值
		handleNum = select(0, &m_fdTempRead, NULL, NULL, &tv);
		count = m_fdRead.fd_count;

		if (handleNum == 0)
		{
			Sleep(100);
		}
		else if (handleNum > 0)
		{
			for (int i = 0; i < count; i++)
			{
				if (FD_ISSET(m_fdRead.fd_array[i], &m_fdTempRead))
				{
					//发生客户端连接事件
					if (m_socket == m_fdRead.fd_array[i])
					{
						SOCKET sClient = accept(m_socket, (SOCKADDR*)&addrClient, &size);
						if (INVALID_SOCKET != sClient)
						{
							FD_SET(sClient, &m_fdRead);
							m_msgManger->setFdArray(m_fdRead);
							cout << "一个客户端连接，当前连接数：" << m_fdRead.fd_count - 1 << endl;
						}
					}
					//接收数据
					else
					{
						ret = recv(m_fdRead.fd_array[i], readBuf, BUFFERSIZE, 0);
						m_msgManger->setFdArray(m_fdRead);
						if (ret == 0 || ret == SOCKET_ERROR)
						{
							closesocket(m_fdRead.fd_array[i]);
							FD_CLR(m_fdRead.fd_array[i], &m_fdRead);
							m_msgManger->setFdArray(m_fdRead);
							cout << "一个客户端断开连接，当前连接数：" << m_fdRead.fd_count - 1 << endl;
						}
						else
						{
							commum::Message *packet = new commum::Message;
							packet->ParseFromArray(readBuf, BUFFERSIZE);
							m_msgManger->insertReceiveMsg(packet);
						}
					}
				}
			}
		}
	}
}
