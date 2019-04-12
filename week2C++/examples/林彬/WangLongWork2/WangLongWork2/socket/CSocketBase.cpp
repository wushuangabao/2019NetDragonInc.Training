#include<iostream>
using namespace std;
#include "CSocketBase.h"

CSocketBase::CSocketBase()
{
	FD_ZERO(&m_fdRead);
	FD_ZERO(&m_fdTempRead);
	socketInit();
}
CSocketBase::CSocketBase(char *ip, unsigned short port)
{
	FD_ZERO(&m_fdRead);
	FD_ZERO(&m_fdTempRead);
	addr.setIP(ip);
	addr.setPort(port);
	socketInit();
}
CSocketBase::~CSocketBase()
{
	Close();
}
void CSocketBase::socketInit()
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &wsaData) != 0)
	{
		cout << "WSAStartup" << WSAGetLastError() << endl;
		WSACleanup();
		exit(0);
	}
}
void CSocketBase::setAddr(char *ip, unsigned short port)
{
	addr.setIP(ip);
	addr.setPort(port);
}
void CSocketBase::setAddr(CAddress &addr)
{
	this->addr = addr;
}

int CSocketBase::Socket(int type)
{
	m_socket = socket(PF_INET, type, 0);
	if(m_socket == INVALID_SOCKET)
	{
		cout << "socket:" << WSAGetLastError() << endl;
		Close();
		exit(0);
	}
	return m_socket;
}
void CSocketBase::Close()
{
	if (m_socket)
	{
		closesocket(m_socket);
	}
	WSACleanup();
}
void CSocketBase::setFd(SOCKET m_socket)
{
	this->m_socket = m_socket;
}
int CSocketBase::getFd()
{
	return m_socket;
}
int CSocketBase::Read(SOCKET socketclient, char *buffer)
{
	int nRead;
	nRead = recv(socketclient, buffer, BUFFERSIZE, 0);
	if(nRead < 0)
	{
		perror("read");
		Close();
		exit(0);
	}
	return nRead;
}
bool CSocketBase::Write(SOCKET socketclient, char* buffer, int size)
{
	if(send(socketclient, buffer,size, 0) < 0 )
	{
		perror("write");
		Close();
		exit(0);
	}
	return true;
}