#include<iostream>
using namespace std;
#include<WINsock2.h>
#include "caddress.h"
CAddress::CAddress()
{
	addr.sin_family=AF_INET;
	iSize=sizeof(struct sockaddr_in);
}
CAddress::~CAddress()
{

}
char * CAddress::getIP()
{
	if(inet_ntoa(addr.sin_addr) == NULL)
	{
		perror("getip");
		exit(0);
	}
	return inet_ntoa(addr.sin_addr);
}
void CAddress::setIP(char *ip)
{
	addr.sin_addr.s_addr=inet_addr(ip);
}
unsigned short CAddress::getPort()
{
	return ntohs(addr.sin_port);
}
void CAddress::setPort(unsigned short port)
{
	addr.sin_port = htons(port);
}
struct sockaddr *CAddress::getPtr()
{
	return (struct sockaddr *)&addr;
}
int CAddress::getSize()
{
	return iSize;
}
int *CAddress::getSizePtr()
{
	return (int *)&iSize;
}