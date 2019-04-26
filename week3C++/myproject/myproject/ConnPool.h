#pragma once

#include <list>
#include <mutex>

using namespace std;

class DB;
class CSql;

class ConnPool
{
public:
	// 获取数据库连接池对象
	static ConnPool* getInstance(DB* db, int size);
	// 得到一条连接
	CSql* getConnect();
	// 归还一条连接
	void retConnect(CSql* ret);
	// 获取连接池的剩余连接数
	size_t getPoolSize();

	~ConnPool();

private:
	static ConnPool *pool; //连接池对象
	mutex lock;            //锁
	int poolSize;          //连接池大小
	list<CSql*> conList;   //连接队列

	// 单例模式 构造函数
	ConnPool(DB* db, int maxSize);
};
