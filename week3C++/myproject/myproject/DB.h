#pragma once

#include <string>
using namespace std;

// 角色类型：游客，用户，管理员
enum role_type { wander, user, admin };

class DB
{
public:
	char user[20] = "root";
	char passwd[20] = "";
	char ip[20] = "localhost";
	char dbname[10] = "chat";

	// 连接池
	MYSQL* con;

	// 记录下一条聊天消息的id
	unsigned int msg_id = 1;

	DB();
	~DB();
	
	void query(string tablename);  //查询数据
	void insert(string tablename);  //添加数据
	void delet(string tablename);  //删除数据
	void update(string tablename);  //更改数据

	bool sql(string sql);  //调用sql语句(只能1句)
	bool transc1(char* name, char* pswd, unsigned int sex, char* act);  //事务处理1：创建people账户，选择actor角色

private:
	MYSQL* connect();  //建立连接

	string roleOf(string user); //查询某个user的角色
	string getTime();  //获取系统时间
	bool CreAcc(char* name, char* pswd, unsigned int sex); //创建people表记录（创建账户）,preparestatement
	void openAutoCommit();  //开启自动提交事务
};