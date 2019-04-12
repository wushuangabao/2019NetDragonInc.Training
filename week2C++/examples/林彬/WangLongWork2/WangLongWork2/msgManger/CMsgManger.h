#pragma once
#include <list>
#include <Mutex>
#include <iostream>
#include "../msgManger/commun.pb.h"
#define MSGCOUNT 10000
#define BUFFSIZE 1024
#include <windows.h>

class CMsgManger
{
public:
	~CMsgManger();
	static CMsgManger * getSingleton();
	//向接收数据队列中插入接受到的数据
	void insertReceiveMsg(void * pdata);
	//从接收数据队列中获取接受到的数据
	void *getReceiveMsg();
	//向发送数据队列中插入要发送的数据
	void insertSendMsg(void * pdata);
	//从发送数据队列中获取要发送的数据
	void *getSendMsg();
	void msgRecvDequeDeal();
	void msgSendDequeDeal();
	void setFdArray(fd_set fdRead);

private:
	CMsgManger();
	static CMsgManger *msgmanger;
	std::list<void *> m_msgRecvList;
	std::list<void *> m_msgSendList;
	std::list<void *>::iterator it;
	HANDLE m_semSendInsertList;
	HANDLE m_semSendGetList;
	HANDLE m_semRecvInsertList;
	HANDLE m_semRecvGetList;
	std::thread  recvThread;
	std::thread  sendThread;
	std::mutex m_recvMutex;
	std::mutex m_sendMutex;
	bool isRun;
	fd_set m_fdRead;

	class CGarBo
	{
	public:
		CGarBo() {}
		~CGarBo()
		{
			if (msgmanger != NULL)
				delete msgmanger;
		}
	};
	static CGarBo GarBo;
};
