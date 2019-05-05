#include <time.h>
#include "DB.h"
#include "CSql.h"
#include "ConnPool.h"

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

////////////////////////////////
/// 创建账户
////////////////////////////////
bool DB::createAccount(string name_s)
{
	// 从线程池中取出连接
	CSql* c = pool->getConnect();

	// 修改数据库提交模式为手动提交
	if (c->openManuCommit())
	{
		// 开始事务处理
		if (c->sql("start transaction;"))
		{
			char* name = (char*)name_s.c_str();
			MYSQL_BIND param[1];
			memset(param, 0, sizeof(param));
			param[0].buffer_type = MYSQL_TYPE_STRING;
			param[0].buffer = name;
			param[0].buffer_length = strlen(name);

			// 新增user记录
			string sql = "insert into user(user_name) values(?);";
			if (c->prepareStmt(sql, param))
			{
				// 新增role记录
				string sql = "insert into role(user_name) values(?);";
				if(c->prepareStmt(sql, param))
				{ 
					// 事务提交
					if (c->commit())
					{
						c->openAutoCommit();
						pool->retConnect(c);
						return true;
					}
				}
				else
				{
					// 事务回滚
					c->rollBack();
				}
			}
			else
			{
				// 事务回滚
				c->rollBack();
			}
		}
	}
	c->openAutoCommit();
	pool->retConnect(c);
	return false;
}

//////////////////////////////
/// 修改用户名
//////////////////////////////
bool DB::changeUserName(string newname, string oldname)
{
	// 从线程池中取出连接
	CSql* c = pool->getConnect();

	// 修改数据库提交模式为手动提交
	if (c->openManuCommit())
	{
		// 开始事务处理
		if (c->sql("start transaction;"))
		{
			char *nameNew = (char*)newname.c_str(),
				*nameOld = (char*)oldname.c_str();
			MYSQL_BIND params[2];
			memset(params, 0, sizeof(params));
			params[0].buffer_type = MYSQL_TYPE_STRING;
			params[0].buffer = nameNew;
			params[0].buffer_length = strlen(nameNew);
			params[1].buffer_type = MYSQL_TYPE_STRING;
			params[1].buffer = nameOld;
			params[1].buffer_length = strlen(nameOld);
			string sql = "update user set user_name=? where(user_name=?);";
			if (c->prepareStmt(sql, params))
			{
				// 事务提交
				if (c->commit())
				{
					c->openAutoCommit();
					pool->retConnect(c);
					return true;
				}
			}
			else
			{
				// 事务回滚
				c->rollBack();
			}
		}
	}
	c->openAutoCommit();
	pool->retConnect(c);
	return false;
}

////////////////////////////
/// 删除用户数据
////////////////////////////
bool DB::deleteUser(string name)
{
	CSql* c = pool->getConnect();
	if (c->openManuCommit())
	{
		if (c->sql("start transaction;"))
		{
			string sql = "select * from user where(user_name='" + name + "');";
			if (c->sql(sql)){
				// 查询name是否存在
				if(c->putOutRes(false)>0){
					sql = "delete from user where(user_name='" + name + "');";
					if (c->sql(sql))
						if (c->commit())
						{
							c->openAutoCommit();
							pool->retConnect(c);
							return true;
						}
						else
							c->rollBack();
				}
				else {
					c->rollBack();
					cout << "用户" << name << "不存在！" << endl;
				}
			}
			else
				c->rollBack();
		}
	}
	c->openAutoCommit();
	pool->retConnect(c);
	return false;
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
