#include "mysql.h"
#include <string>
#pragma comment(lib,"libmySQL.lib")
using namespace std;

class DB
{
public:
	char user[20] = "root";
	char passwd[20] = "";
	char ip[20] = "localhost";
	char dbname[20] = "gamedb";
	MYSQL * con;
	unsigned int msg_id = 1;  // 记录下一条聊天消息的id

	~DB();
	MYSQL* connect();  //建立连接
	void query();  //查询所有表中的数据
	void query(string tablename);  //查询某一张表中的数据
	void insert(string tablename);  //添加数据，针对people用户表与msg聊天记录表
	void delet(string tablename);  //删除数据，针对people用户表
	void update(string tablename);  //更改数据，针对people用户表与actor角色表

	bool sql(string sql);  //调用sql语句(只能1句)
	bool transc1(char* name, char* pswd, unsigned int sex, char* act);  //事务处理1：创建people账户，选择actor角色

private:
	string userOf(string actor); //查询某个actor对应的user
	string actorOf(string user); //查询某个user对应的actor
	string getTime();  //获取系统时间
	bool CreAcc(char* name, char* pswd, unsigned int sex); //创建people表记录（创建账户）,preparestatement
	void openAutoCommit();  //开启自动提交事务
};
