#pragma once
#include <WinSock2.H> 
#include <WS2tcpip.h> 

#pragma comment(lib, "ws2_32.lib") 
class CAddress{
public:
	CAddress();
	~CAddress();
	char *getIP();
	void setIP(char *ip);
	unsigned short getPort();
	void setPort(unsigned short port);
	struct sockaddr *getPtr();
	int getSize();
	int *getSizePtr();
private:
	struct sockaddr_in addr;
	int iSize;
};