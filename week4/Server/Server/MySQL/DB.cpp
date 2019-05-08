#include <time.h>
#include <iostream>
#include "DB.h"
#include "CSql.h"
#include "ConnPool.h"

using namespace std;

DB* DB::db = nullptr;

DB::DB()
{
	pool = ConnPool::getInstance(this, poolSize);
}

DB::~DB()
{
	delete pool;
	pool = nullptr;
	db = nullptr;
	cout << "db已销毁！" << endl;
}

DB* DB::getInstance()
{
	if (db == nullptr)
		db = new DB();
	return db;
}

// 输出所有表
void DB::printAllTable() 
{
	// 获取连接
	CSql* con = pool->getConnect();

	cout << getTime() << " 输出数据库chat内容：" << endl;
	cout << "----------- user ------------" << endl;
	string tmp = "select * from user";
	con->sql(tmp);
	con->putOutRes();
	cout << "----------- role ------------" << endl;
	tmp = "select * from role";
	con->sql(tmp);
	con->putOutRes();
	cout << "---------- record -----------" << endl;
	tmp = "select * from record";
	con->sql(tmp);
	con->putOutRes();

	// 归还连接
	pool->retConnect(con);
}

// 创建账户
bool DB::createAccount(string name_s, string passwd)
{
	// 从线程池中取出连接
	CSql* c = pool->getConnect();

	char* name = (char*)name_s.c_str();
	char* pswd = (char*)passwd.c_str();
	MYSQL_BIND param[2];
	memset(param, 0, sizeof(param));
	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = name;
	param[0].buffer_length = strlen(name);
	param[1].buffer_type = MYSQL_TYPE_STRING;
	param[1].buffer = pswd;
	param[1].buffer_length = strlen(pswd);
	string sql = "insert into user(user_name,pass_word) values(?,?);";
	if (c->prepareStmt(sql, param))
	{
		pool->retConnect(c);
		return true;
	}
	else
	{
		pool->retConnect(c);
		return false;
	}
}

/**
 * @brief 校验用户名、密码
 *
 * @param name 用户名
 * @param passwd 密码
 * @return int 0:校验成功 1:用户名不存在 2:密码错误 3:其它原因导致校验失败
**/
int DB::checkAccount(string name, string passwd)
{
	CSql* c = pool->getConnect();
	if (c->openManuCommit())
	{
		if (c->sql("start transaction;"))
		{
			string sql = "select * from user where(user_name='" + name + "');";
			if (c->sql(sql)) {
				// 查询name是否存在
				if (c->putOutRes(false) == 1) {
					sql = "select * from user where(user_name='" + name + "' and pass_word='" + passwd + "');";
					if (c->sql(sql))
						// 查询passwd是否存在
						if (c->putOutRes(false) == 1)
						{
							c->openAutoCommit();
							pool->retConnect(c);
							return 0;
						}
						else {
							c->rollBack();
							cout << "密码错误！" << endl;
							c->openAutoCommit();
							pool->retConnect(c);
							return 2;
						}
				}
				else {
					c->rollBack();
					cout << "用户" << name << "不存在！" << endl;
					c->openAutoCommit();
					pool->retConnect(c);
					return 1;
				}
			}
		}
	}
	c->rollBack();
	c->openAutoCommit();
	pool->retConnect(c);
	return 3;
}

// 新增聊天记录
 bool DB::createChatRecord(string name_s, string msg_s)
 {
	 //INSERT INTO `chat_record` (`time`, `user_name`, `msg`) VALUES ('2019-05-07 13:59:43', 'admin', '兄弟们在吗？')
	 CSql* c = pool->getConnect();
	 char* name = (char*)name_s.c_str();
	 char* msg = (char*)msg_s.c_str();
	 MYSQL_BIND param[2];
	 memset(param, 0, sizeof(param));
	 param[0].buffer_type = MYSQL_TYPE_STRING;
	 param[0].buffer = name;
	 param[0].buffer_length = strlen(name);
	 param[1].buffer_type = MYSQL_TYPE_VARCHAR;
	 param[1].buffer = msg;
	 param[1].buffer_length = strlen(msg);
	 string sql = "insert into chat_record(time,user_name,msg) values(\'" + getTime() + "\',?,?);";
	 if (c->prepareStmt(sql, param))
	 {
		 pool->retConnect(c);
		 return true;
	 }
	 else
	 {
		 pool->retConnect(c);
		 return false;
	 }
 }

// 获取系统时间
string DB::getTime()
{
	char tmp[32];
	struct tm timeInfo;
	time_t t = time(0);
	localtime_s(&timeInfo, &t);
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %X", &timeInfo);

	return string(tmp);
}
