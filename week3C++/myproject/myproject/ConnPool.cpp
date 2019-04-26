#include "pch.h"
#include "CSql.h"
#include "ConnPool.h"

using namespace std;

ConnPool* ConnPool::pool = nullptr;

// 构造函数(private)
ConnPool::ConnPool(DB* db, int maxSize)
	: poolSize(maxSize)
{
	// 加锁（变量析构时自动解锁）
	lock_guard<mutex> locker(lock);

	// 创建poolSize个连接
	for (int i = 0; i < poolSize; ++i)
	{
		CSql* p = new CSql(db);
		conList.push_back(p);
	}
}

// 销毁连接池
ConnPool::~ConnPool()
{
	for (auto p : conList)
	{
		delete p;
	}
	pool = nullptr;
	cout << "连接池已销毁！" << endl;
}

size_t ConnPool::getPoolSize()
{
	return conList.size();
}

ConnPool* ConnPool::getInstance(DB* db, int size)
{
	if (pool == nullptr)
		pool = new ConnPool(db, size);
	return pool;
}

CSql* ConnPool::getConnect()
{
	lock_guard<mutex> locker(lock);
	CSql* p = conList.front();
	conList.pop_front();
	return p;
}

void ConnPool::retConnect(CSql* ret)
{
	lock_guard<mutex>locker(lock);
	conList.push_back(ret);
}
