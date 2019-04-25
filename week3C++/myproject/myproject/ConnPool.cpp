#include "pch.h"
#include "ConnPool.h"
#include "mysql_connect.h"

using namespace std;

ConnPool* ConnPool::pool = nullptr;

// 构造函数(private)
ConnPool::ConnPool(string name, string pwd, string nurl, int maxSize) :	username(name), password(pwd), url(nurl), poolSize(maxSize)
{
	driver = get_driver_instance(); //获取mysql驱动
	lock_guard<mutex> locker(lock); //加锁（变量析构时自动解锁）
	addConn(poolSize);              //增添连接
}

// 销毁连接池
ConnPool::~ConnPool()
{
	for (auto &conn : conList)
	{
		// 依次转移所有权，出作用域时，关闭连接，出作用域时智能指针自动释放
		shared_ptr<Connection> &&sp = move(conList.front());
		sp->close();
	}
}

int ConnPool::getPoolSize()
{
	return conList.size();
}

void ConnPool::addConn(int size)
{
	for (int i = 0; i < size; ++i)
	{
		// 创建连接
		Connection *conn = driver->connect(url, username, password);
		shared_ptr<Connection> sp(conn, [](Connection *conn) {	delete conn; });
		conList.push_back(move(sp));
	}
}

ConnPool* ConnPool::getInstance()
{
	if (pool == nullptr)
		pool = new ConnPool("root", "", "127.0.0.1:3306", 10); //创建10个连接
	return pool;
}

shared_ptr<Connection> ConnPool::getConnect()
{
	lock_guard<mutex> locker(lock);
	shared_ptr<Connection> sp = conList.front();
	conList.pop_front();
	return sp;
}

void ConnPool::retConnect(shared_ptr<Connection> &ret)
{
	lock_guard<mutex>locker(lock);
	conList.push_back(ret);
}
