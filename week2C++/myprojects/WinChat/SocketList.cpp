#include "SocketList.h"

SocketList::SocketList(bool IsServer, string ConnectIp) :isServer(IsServer)
{
	zerotime.tv_usec = 0;
	zerotime.tv_sec = 0;
	if (isServer)
		ConnectSocket = new ListenSocket;
	else
	{
		ConnectSocket = new DataSocket;
		DataSocket* dataSocket = dynamic_cast<DataSocket*> (ConnectSocket);
		dataSocket->RequestConnect(ConnectIp);
	}
}

SocketList::~SocketList()
{
	delete ConnectSocket;
	for (list<DataSocket*>::iterator itr = SerDatSockList.begin();
		itr != SerDatSockList.end(); itr++)
	{
		delete *itr;
	}
}

void SocketList::Send(string str)
{
	if (isServer)
		SendToAllClient(str);
	else
		SendToServer(str);
}

list<string> SocketList::Listening(DataSocket **RecSocket)
{
	chat::data proto_data;
	list<string> retDataList;
	FD_ZERO(&rset);// 初始化rset为NULL
	FD_SET(ConnectSocket->GetSocket(), &rset);// 添加连接所用套接字
	if (isServer)
	{
		// 添加所有数据套接字链表
		for (list<DataSocket*>::iterator itr = SerDatSockList.begin();itr != SerDatSockList.end(); itr++)
		{
			FD_SET((*itr)->GetSocket(), &rset);
		}
	}
	// 查找在rset中是否有活动的套接字
	int i = select(0x7FFFFFFF, &rset, NULL, NULL, &zerotime);
	if (i > 0)
	{
		if (!isServer)  //客户端
		{
			DataSocket* dataSocket = dynamic_cast<DataSocket*> (ConnectSocket);
			if (FD_ISSET(dataSocket->GetSocket(), &rset)) //接收到服务器发来的信息mes
			{
				string mes = dataSocket->ReceiveData();
				if (mes == "SocketClosed")
				{
					MessageBox(NULL, L"The server is closed!", L"Prompt", 0);
					exit(0);
				}
				proto_data.set_ins(mes);
				string* output = NULL;
				output = new string;
				proto_data.SerializeToString(output);
				retDataList.push_back(*output + "#end#");//信息入表，等待Chat类的处理
				delete output;
			}
		}
		else if (isServer) //服务端
		{
			ListenSocket* listenSocket = dynamic_cast<ListenSocket*> (ConnectSocket);
			if (FD_ISSET(listenSocket->GetSocket(), &rset)) //监听Socket受到连接请求
			{
				DataSocket *dsock = listenSocket->AcceptConnect();// 接收连接
				SerDatSockList.push_back(dsock);// 接收的数据套接字入表
				*RecSocket = dsock;
				proto_data.set_ins("Connected");
				string* output = NULL;
				output = new string;
				proto_data.SerializeToString(output);
				retDataList.push_back(*output + "#end#");//信息入表，等待Chat类的处理
				delete output;
			}
			// 遍历每个socket检查是否有活动
			for (list<DataSocket*>::iterator itr = SerDatSockList.begin();itr != SerDatSockList.end(); itr++)
			{
				if (FD_ISSET((*itr)->GetSocket(), &rset))
				{
					string mes = (*itr)->ReceiveData();
					if (mes == "SocketClosed")  //客户端关闭信息
					{
						delete (*itr);
						itr = SerDatSockList.erase(itr);
						if (itr == SerDatSockList.end())
							break;
						continue;
					}
					else  //其他信息
					{
						proto_data.set_ins(mes);
						string* output = NULL;
						output = new string;
						proto_data.SerializeToString(output);
						retDataList.push_back(*output + "#end#");//信息入表，等待Chat类的处理
						delete output;
						*RecSocket = *itr;
					}
				}
			}
			//endfor
			if (retDataList.size() != 0)
			{
				SendToAllClient(retDataList);
			}
		}
	}
	return retDataList;
}

void SocketList::SendToAllClient(list<string> StrList)
{
	for (list<string>::iterator sItr = StrList.begin(); sItr != StrList.end(); sItr++)
	{
		SendToAllClient(*sItr);
	}
}

void SocketList::SendToAllClient(string str)
{
	for (list<DataSocket*>::iterator itr = SerDatSockList.begin();itr != SerDatSockList.end(); itr++)
	{
		(*itr)->SendData(str);
	}
}

void SocketList::SendToServer(string str)
{
	DataSocket *dataSocket = dynamic_cast<DataSocket *>(ConnectSocket);
	dataSocket->SendData(str);
}