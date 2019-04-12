#include "CClient.h"

//变量
SOCKET  sClient1;
HANDLE	hThreadRecv;						//接收数据线程
BOOL	bConnecting;						//与服务器的连接状态
HANDLE	arrThread[1];						//子线程数组

CClient::CClient()
{
	sClient = INVALID_SOCKET;	//套接字
	sClient1 = INVALID_SOCKET;	//套接字
	hThreadRecv = NULL;			//接收数据线程句柄
	bConnecting = FALSE;		//为连接状态

								//初始化数据缓冲区
	memset(arrThread, 0, 2);
}


CClient::~CClient()
{
	CloseHandle(hThreadRecv);
	closesocket(sClient);
	WSACleanup();
}
//连接服务器
BOOL CClient::ConnectServer(void)
{
	WSAStartup(MAKEWORD(2, 0), &wsa);	//初始化WS2_32.DLL

	//创建套接字
	if ((sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		printf("套接字socket创建失败!\n");
		return false;
	}
	sClient1 = sClient;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(5000);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//请求连接
	printf("尝试连接中...\n");
	if (connect(sClient, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		printf("连接失败!\n");
		return false;
	}
	printf("连接成功!\n");
	bConnecting = TRUE;
	return true;
}

bool CClient::sendData(SOCKET s, char * str, int size)
{
	//发送数据
	int bytecount = 0;
	if ((bytecount = send(sClient, str, size, 0)) == -1) {
		fprintf(stderr, "Error sending data %d\n", errno);
		//closesocket(clientsocket);
		return false;
	}
	printf("Sent bytes %d\n", bytecount);
	return true;
}

google::protobuf::uint32 readHdr(char *buf)
{
	google::protobuf::uint32 size;
	google::protobuf::io::ArrayInputStream ais(buf, 4);
	CodedInputStream coded_input(&ais);
	coded_input.ReadVarint32(&size);//Decode the HDR and get the size
	//cout << "size of payload is " << size << endl;
	return size;
}
//数据包解析
void ReadMsg(SOCKET csock, google::protobuf::uint32 siz)
{
	int bytecount;
	log_packet payload;
	char *buffer = new char[siz + 4];//size of the payload and hdr
									 //Read the entire buffer including the hdr
	if ((bytecount = recv(csock, buffer, siz + 4, MSG_WAITALL)) == -1) {
		fprintf(stderr, "Error receiving data %d\n", errno);
	}
	//cout << "Second read byte count is " << bytecount << endl;
	//Assign ArrayInputStream with enough memory 
	//google::protobuf::io::ArrayOutputStream
	google::protobuf::io::ArrayInputStream ais(buffer, siz + 4);
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
	cout << "接收到数据： " << endl;
	cout << payload.DebugString() << endl;
}

DWORD WINAPI RecvDataThread(void * pParam)
{
	int		reVal;				    //返回值
	char    bufRecv[4];   //接收数据缓冲区

	while (bConnecting)			    //连接状态
	{
		memset(bufRecv, 0, 4);
		reVal = recv(sClient1, bufRecv, 4, MSG_PEEK);//接收数据
		if (SOCKET_ERROR == reVal)
		{
			int nErrCode = WSAGetLastError();
			if (WSAEWOULDBLOCK == nErrCode)			//接受数据缓冲区不可用
			{
				continue;							//继续接收数据
			}
			else {
				bConnecting = FALSE;
				return 0;							//线程退出
			}
		}

		if (reVal == 0)							//服务器关闭了连接
		{
			bConnecting = FALSE;
			return 0;								//线程退出
		}
		if (reVal > 0)
		{
			ReadMsg(sClient1, readHdr(bufRecv));
		}
	}
	return 0;
}


BOOL CClient::CreateSendAndRecvThread(void)
{
	// 创建接收数据的线程
	unsigned long ulThreadId;
	hThreadRecv = CreateThread(NULL, 0, RecvDataThread, NULL, 0, &ulThreadId);
	if (NULL == hThreadRecv)
		return FALSE;

	//添加到线程数组
	arrThread[0] = hThreadRecv;
	return TRUE;
}
