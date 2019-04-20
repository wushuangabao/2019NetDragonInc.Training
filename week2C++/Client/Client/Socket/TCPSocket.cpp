#include "TCPSocket.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;
using namespace std;

const int Max_Name = 20;
WSADATA g_wsadata;      // winsock data holder
BaseSocket::BaseSocket(int PassSocket) :sock(PassSocket), port(4000)
{
	if (PassSocket == -1)
		CreateSock();
	socketaddress.sin_family = AF_INET;                 // 设置网络类型
	socketaddress.sin_port = htons(port);               // 使用端口
	socketaddress.sin_addr.s_addr = htonl(INADDR_ANY);  // 允许绑定到任何地址的套接字
	memset(&(socketaddress.sin_zero), 0, 8);            // 清除填充区
}

void BaseSocket::CreateSock() {
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1)
	{
		MessageBox(NULL, L"Socket cannot creat!", L"Prompt", 0);
		exit(0);
	}
}

void BaseSocket::CloseSock()
{
	shutdown(sock, 2);
	CloseSocket(sock);
}

BaseSocket::~BaseSocket() { CloseSock(); }

int BaseSocket::GetSocket() { return sock; }

DataSocket::DataSocket(int PassSocket) : BaseSocket(PassSocket) {}

void DataSocket::RequestConnect(std::string address)
{
	socketaddress.sin_family = AF_INET;
	socketaddress.sin_port = htons(port);
	socketaddress.sin_addr.s_addr = inet_addr(address.c_str());
	memset(&(socketaddress.sin_zero), 0, 8);

	if (connect(sock, (struct sockaddr *)&socketaddress, sizeof(struct sockaddr)) == -1)
		cout << "Connet failed!" << endl;
	else
		cout << "Connet success!" << endl;
}

int DataSocket::SendData(std::string str)
{
	return send(sock, str.c_str(), str.length(), 0);
}

std::string DataSocket::ReceiveData()
{
	char buffer[512];
	string retStr;
	memset(buffer, 0, 512);
	int received;
	received = recv(sock, buffer, 512, 0);
	if (received == -1)
	{
		strcpy(buffer, string("SocketClosed").c_str());
	}
	return std::string(buffer);
}