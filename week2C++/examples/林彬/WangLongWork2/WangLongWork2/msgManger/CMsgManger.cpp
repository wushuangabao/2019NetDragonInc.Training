#include "CMsgManger.h"

CMsgManger * CMsgManger::msgmanger = NULL;
CMsgManger::CGarBo CMsgManger::GarBo;
CMsgManger::CMsgManger()
{
	isRun = true;
	m_semSendInsertList = CreateSemaphore(NULL, MSGCOUNT, MSGCOUNT, NULL);
	m_semSendGetList = CreateSemaphore(NULL, 0, MSGCOUNT, NULL);
	m_semRecvInsertList = CreateSemaphore(NULL, MSGCOUNT, MSGCOUNT, NULL);
	m_semRecvGetList = CreateSemaphore(NULL, 0, MSGCOUNT, NULL);
	recvThread = std::thread(&CMsgManger::msgRecvDequeDeal, this);
	sendThread = std::thread(&CMsgManger::msgSendDequeDeal, this);
}

CMsgManger::~CMsgManger()
{
	isRun = false;
	CloseHandle(m_semSendInsertList);
	CloseHandle(m_semSendGetList);
	CloseHandle(m_semRecvInsertList);
	CloseHandle(m_semRecvGetList);
	m_msgRecvList.clear();
	m_msgSendList.clear();
}

CMsgManger * CMsgManger::getSingleton()
{
	if (NULL == msgmanger)
	{
		msgmanger = new CMsgManger();
	}
	return msgmanger;
}

void CMsgManger::insertReceiveMsg(void * pdata)
{
	if (pdata)
	{
		WaitForSingleObject(m_semRecvInsertList, INFINITE);
		m_recvMutex.lock();
		m_msgRecvList.push_back(pdata);
		m_recvMutex.unlock();
		ReleaseSemaphore(m_semRecvGetList, 1, NULL);
	}
}

void *CMsgManger::getReceiveMsg()
{
	void *msg;
	WaitForSingleObject(m_semRecvGetList, INFINITE);
	m_recvMutex.lock();
	if (!m_msgRecvList.empty())
	{
		it = m_msgRecvList.begin();
		msg = *it;
		m_msgRecvList.pop_front();
	}
	m_recvMutex.unlock();
	ReleaseSemaphore(m_semRecvInsertList, 1, NULL);
	return msg;
}

void CMsgManger::insertSendMsg(void * pdata)
{
	if (pdata)
	{
		WaitForSingleObject(m_semSendInsertList, INFINITE);
		m_sendMutex.lock();
		m_msgSendList.push_back(pdata);
		m_sendMutex.unlock();
		ReleaseSemaphore(m_semSendGetList, 1, NULL);
	}
}

void *CMsgManger::getSendMsg()
{
	void *msg;
	WaitForSingleObject(m_semSendGetList, INFINITE);
	m_sendMutex.lock();
	if (!m_msgSendList.empty())
	{
		it = m_msgSendList.begin();
		msg = *it;
		m_msgSendList.pop_front();
	}
	m_sendMutex.unlock();
	ReleaseSemaphore(m_semSendInsertList, 1, NULL);
	return msg;
}

void CMsgManger::msgRecvDequeDeal()
{
	while (isRun)
	{
		if (!m_msgRecvList.empty())
		{
			insertSendMsg(getReceiveMsg());
		}
	}
}

void CMsgManger::msgSendDequeDeal()
{
	char sendBuf[BUFFSIZE] = { 0 };
	commum::Message *packet;
	while (isRun)
	{
		if (!m_msgSendList.empty())
		{
			memset(sendBuf, 0, BUFFSIZE);
			packet = (commum::Message *)getSendMsg();
			packet->SerializeToArray(sendBuf, BUFFSIZE);
			for (int i = 0; i < m_fdRead.fd_count; i++)
			{
				if (m_fdRead.fd_array[i] != 0)
				{
					send(m_fdRead.fd_array[i], sendBuf, BUFFSIZE, 0);
				}
			}
			delete packet;
		}
	}
}

void CMsgManger::setFdArray(fd_set fdRead)
{
	m_fdRead = fdRead;
}

