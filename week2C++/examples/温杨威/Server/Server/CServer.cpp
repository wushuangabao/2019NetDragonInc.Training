

#include "CServer.h"
#include <iostream>
#include <WS2tcpip.h>

using namespace std;
#define SERVER_PORT 5000
#define MSG_BUF_SIZE 1024
ClIENTVECTOR clientvector;                  //存储子套接字
CServer::CServer()
{
	//初始化服务器
	cout << "Server 初始化...\n";
	//地址长度
	addr_len = sizeof(SOCKADDR_IN);
	//sin_family指代协议族，在socket编程中只能是AF_INET
	addr_server.sin_family = AF_INET;
	//sin_port存储端口号（使用网络字节顺序），普通数字可以用htons()函数转换成网络数据格式的数字)
	addr_server.sin_port = htons(SERVER_PORT);
	//sin_addr存储IP地址，使用in_addr这个数据结构
	//address in network byte order（Internet address）
	//ADDR_ANY,监听所有地址
	addr_server.sin_addr.S_un.S_addr = ADDR_ANY;
	//对buf_ip进行初始化
	wmemset(buf_ip, 0, IP_BUF_SIZE);
	//WSAStartup,该函数第一个参数为WS2_32.DLL版本，通常设为MAKEWORD(2,0)，
	//第二个参数为一个指向WSADATA的指针，用于返回WS2_32.DLL的配置信息
	rec_val = WSAStartup(MAKEWORD(2, 0), &wsa_data);
	//判断，若不为0，则WS2_32.DLL 初始化失败
	if (rec_val != 0)
	{
		cerr << "WSA 初始化失败!Error code: " << WSAGetLastError() << "\n";
		system("pause");
		exit(1);
	}
	//正常运行，WS2_32.DLL 初始化成功
	cout << "WSA 初始化成功...\n";
	//创建族地址为AF_INET，TCP连接，AF_INET族地址TCP协议的套接字
	sock_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//若返回socket的INVALID_SOCKET，则生成socket失败
	if (sock_server == INVALID_SOCKET)
	{
		cerr << "创建server socket失败!Error code: " << WSAGetLastError() << "\n";
		//释放WS2_32.DLL
		WSACleanup();
		system("pause");
		exit(1);
	}
	//生成socket成功
	cout << "Server socket 创建成功...\n";
	//绑定socket
	rec_val = bind(sock_server, (SOCKADDR*)&addr_server, addr_len);
	if (rec_val != 0)
	{
		//绑定失败
		cerr << "绑定server socket失败!Error code: " << WSAGetLastError() << "\n";
		WSACleanup();
		system("pause");
		exit(1);
	}
	//绑定成功
	cout << "Server socket 绑定成功...\n";
	//监听socket
	rec_val = listen(sock_server, SOMAXCONN);
	if (rec_val == SOCKET_ERROR)
	{
		//创建监听失败
		cerr << "Server socket 创建监听失败!Error code: " << WSAGetLastError() << "\n";
		WSACleanup();
		system("pause");
		exit(1);
	}
	//创建监听成功，开始监听
	cout << "Server socket 开始监听...\n";
	//服务器成功启动
	cout << "Server 成功启动..." << endl;
}


CServer::~CServer()
{
	//关闭server socket
	closesocket(sock_server);
	//关闭client socket
	closesocket(sock_client);
	//释放WS2_32.DLL
	WSACleanup();
}
//声明创建客户端线程函数，新线程所执行的线程函数地址
DWORD WINAPI CreateClientThread(LPVOID lpParameter);

void CServer::WaitForClient()
{
	while (true)
	{
		//接受连接请求
		sock_client = accept(sock_server, (SOCKADDR*)&addr_client, &addr_len);
		if (sock_client == INVALID_SOCKET)
		{
			//连接失败
			cerr << "Failed to accept client!Error code: " << WSAGetLastError() << "\n";
			WSACleanup();
			system("pause");
			exit(1);
		}
		//连接成功，存储client数据
		//CClient *pClient = new CClient(sock_client, addr_client);
		clientvector.insert(pair<SOCKET,bool>(sock_client,true));
		//转换client ip地址
		InetNtop(addr_client.sin_family, &addr_client, buf_ip, IP_BUF_SIZE);
		//输出wchar_t数组
		wcout << "A new client connected...IP address: " << buf_ip << ", port number: " << ntohs(addr_client.sin_port) << endl;
		//创建新线程
		//h_thread = _beginthreadex(nullptr, 0, CreateClientThread, (LPVOID)sock_client, 0, nullptr);
		h_thread = CreateThread(nullptr, 0, CreateClientThread, (LPVOID)sock_client, 0, nullptr);
		if (h_thread == NULL)
		{
			//创建失败
			cerr << "Failed to create a new thread!Error code: " << ::WSAGetLastError() << "\n";
			WSACleanup();
			system("pause");
			exit(1);
		}
		//释放句柄
		CloseHandle(h_thread);
	}
}

google::protobuf::uint32 readHdr(char *buf)
{
	google::protobuf::uint32 size;
	google::protobuf::io::ArrayInputStream ais(buf, 4);
	CodedInputStream coded_input(&ais);
	coded_input.ReadVarint32(&size);//Decode the HDR and get the size
	cout << "size of payload is " << size << endl;
	return size;
}
//数据包解析
void CServer::ReadMsg(SOCKET csock, google::protobuf::uint32 siz)
{
	int bytecount;
	log_packet payload;
	char *buffer = new char[siz + 4];//size of the payload and hdr
									 //Read the entire buffer including the hdr
	if ((bytecount = recv(csock, buffer, siz + 4, MSG_WAITALL)) == -1) {
		fprintf(stderr, "Error receiving data %d\n", errno);
	}
	cout << "Second read byte count is " << bytecount << endl;
	//Assign ArrayInputStream with enough memory 
	//google::protobuf::io::ArrayOutputStream
	google::protobuf::io::ArrayInputStream ais(buffer, siz+4);
	CodedInputStream coded_input(&ais);
	//Read an unsigned integer with Varint encoding, truncating to 32 bits.
	coded_input.ReadVarint32(&siz);
	//After the message's length is read, PushLimit() is used to prevent the CodedInputStream 
	//from reading beyond that length.Limits are used when parsing length-delimited 
	//embedded messages
	google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);
	//De-Serialize
	payload.ParseFromCodedStream(&coded_input);
	//Once the embedded message has been parsed, PopLimit() is called to undo the limit
	coded_input.PopLimit(msgLimit);
	//Print the message
	cout << "Message is " << payload.DebugString() << endl;
	//广播
	ClIENTVECTOR::iterator iter = clientvector.begin();
	while (iter != clientvector.end()) {
		//不发送给自己
		if (csock != iter->first)
		{
			SendData(iter->first, payload);
		}
		iter++;
	}
}
void CServer::SendData(SOCKET client, log_packet payload)
{
	//数据序列化封装
	int siz = payload.ByteSize() + 4;
	char *pkt = new char[siz];
	google::protobuf::io::ArrayOutputStream aos(pkt, siz);
	CodedOutputStream *coded_output = new CodedOutputStream(&aos);
	coded_output->WriteVarint32(payload.ByteSize());
	payload.SerializeToCodedStream(coded_output);

	//发送数据
	int bytecount = 0;
	if ((bytecount = send(client, pkt, siz, 0)) == -1) {
		fprintf(stderr, "Error sending data %d\n", errno);
		//closesocket(clientsocket);
	}
	printf("Sent bytes %d\n", bytecount);
}
DWORD WINAPI CreateClientThread(LPVOID lpParameter)
{
	SOCKET sock_clt = (SOCKET)lpParameter;
	char buf_msg[4];
	int ret_val = 0;
	int snd_result = 0;
	log_packet log;
	//循环接收
	do
	{
		memset(buf_msg, 0, 4);
		//将接收的数据赋值给buf_msg
		ret_val = recv(sock_clt, buf_msg, 4, MSG_PEEK);
		//判断数据是否接收成功
		if (ret_val > 0)
		{
			cout << "First read byte count is " << ret_val << endl;
			//接收成功，对数据进行处理
			CServer::ReadMsg(sock_clt,readHdr(buf_msg));
			//CServer::SendData(sock_clt);
			//log.ParseFromArray(buf_msg, 1024);
			//send(sock_clt, buf_msg, 1024, MSG_PEEK);
			//cout << log.Utf8DebugString() << endl;
		}
		else if (ret_val == 0)
		{
			//断开连接
			cout << "connection closed..." << endl;
		}
		else
		{
			//接收错误数据
			cerr << "Failed to receive message from client!Error code: " << GetLastError() << "\n";
		}
	} while (ret_val > 0);
	//关闭socket
	ClIENTVECTOR::iterator key = clientvector.find(sock_clt);
	if (key != clientvector.end())
	{
		clientvector.erase(key);
	}
	closesocket(sock_clt);
	return 0;
}
