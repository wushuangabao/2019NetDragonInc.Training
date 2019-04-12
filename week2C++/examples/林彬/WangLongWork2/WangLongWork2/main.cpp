#include <WinSock2.H> 
#include <WS2tcpip.h> 
#include <iostream>  
#include "socket/CTcpServer.h"
#include "socket/CSocketBase.h"
#include "address/caddress.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")   

int main()
{
	cout << "服务器开始运行" << endl; 
	CTcpServer server(IPADDRESS, PORT);
	server.clientListen();
	server.Recv();
}