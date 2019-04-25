#pragma once

//c++
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <functional>

//mysql driver
#include <mysql_driver.h>
#include <mysql_connection.h>

//mysql execute
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <exception>

//thread mutex 
#include <mutex>

using namespace sql;
using namespace std;

class ConnPool
{
public:
	// 获取数据库连接池对象
	static ConnPool* getInstance();
	// 得到一条连接
	shared_ptr<Connection> getConnect();
	// 归还一条连接
	void retConnect(shared_ptr<Connection> &ret);

	~ConnPool();
	int getPoolSize();

private:
	static ConnPool *pool; //连接池对象
	mutex lock;       //锁
	Driver *driver;        //mysql driver
	int poolSize;          //连接池大小
	string username;
	string password;
	string url;
	list<shared_ptr<Connection>> conList; //连接队列

	ConnPool(string name, string pwd, string nurl, int maxSize);
	void addConn(int size);
};
