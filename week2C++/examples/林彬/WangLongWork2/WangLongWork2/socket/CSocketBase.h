#pragma once
#include "../address/caddress.h"
#include <WS2tcpip.h>  
#include <WinSock2.H>  
#include <map>

#pragma comment(lib, "ws2_32.lib")   
#define IPADDRESS "127.0.0.1"
#define PORT 4799
#define BUFFERSIZE 1024

class CSocketBase
{
public:
	CSocketBase();
	CSocketBase(char *ip,unsigned short port);
	~CSocketBase();
	void socketInit();
	void setAddr(char *ip,unsigned short port);
	void setAddr(CAddress &addr);
	int Socket(int type);
	void Close();
	void setFd(SOCKET m_socket);
	int getFd();
	int Read(SOCKET socketclient, char* buffer);
	bool Write(SOCKET socketclient, char* buffer, int size);
protected:	
	CAddress addr;
	SOCKET m_socket;
	fd_set m_fdRead;
	fd_set m_fdTempRead;
};