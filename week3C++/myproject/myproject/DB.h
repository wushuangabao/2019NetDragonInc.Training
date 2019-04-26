#pragma once

using namespace std;

class CSql;
class ConnPool;

// 角色类型：用户，游客，管理员
enum RoleType { user, wander, admin };

class DB
{
public:
	~DB();

	// 获取单例对象
	static DB* getInstance();

	// 创建user账户
	bool createAccount(string name);
	// 修改用户名
	bool changeUserName(string newname, string oldname);
	// 删除某用户
	bool deleteUser(string name);
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
	string dbname = "chat";
	int port = 3306;

	// 连接池
	ConnPool* pool;
	int poolSize = 5; //大小为5
	
	// 获取系统时间
	string getTime();
};