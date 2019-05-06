#pragma once

using namespace std;

class CSql;
class ConnPool;

class DB
{
public:
	~DB();

	// 获取单例对象
	static DB* getInstance();

	// 创建user账户
	bool createAccount(string name, string passwd);

    // 校验用户名、密码
	// 0:校验成功 1:用户名不存在 2:密码错误 3:其它原因导致校验失败
	int checkAccount(string name, string passwd);

	// 输出所有表
	void printAllTable();

private:
	// SQL操作类
	friend CSql;

	// 数据库
	DB();
	static DB* db;
	string username = "root";
	string passwd = "";
	string ip = "localhost";
	string dbname = "game";
	int port = 3306;

	// 连接池
	ConnPool* pool;
	int poolSize = 5; //大小为5
	
	// 获取系统时间
	string getTime();
};