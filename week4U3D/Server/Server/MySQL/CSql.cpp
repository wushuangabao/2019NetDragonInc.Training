#include <mysql.h>
#include <iostream>
#include <list>
#include "CSql.h"
#include "DB.h"

using namespace std;

// 构造函数
CSql::CSql(DB* parent)
{
	db = parent;

	con = mysql_init(NULL); //初始化Mysql数据库
    
	if (con != NULL && mysql_real_connect(
		con, db->ip.c_str(), db->username.c_str(),
		db->passwd.c_str(), db->dbname.c_str(),
		db->port, NULL, 0))
	{
		// 设定当前激活的数据库
		if (!mysql_select_db(con, db->dbname.c_str()))
		{
			cout << db->dbname << "数据库连接成功!" << endl;
			con->reconnect = 1;

			// 设置中文编码
			if (mysql_real_query(con, "SET NAMES GBK;", strlen("SET NAME GBK;")))
			{
				cout << "字符集设置失败: " << mysql_error(con) << endl;
				system("pause");
				exit(0);
			}
		}
	}
	else
	{
		cout << db->dbname << "数据库连接失败: " << mysql_error(con) << endl;
		system("pause");
		exit(0);
	}
}

// 析构函数
CSql::~CSql()
{
	mysql_close(con);
	cout << "释放了1个连接！" << endl;
}


// 执行一条sql语句
bool CSql::sql(string sql_s)
{
	const char* sql = sql_s.c_str();
	int rt = mysql_real_query(con, sql, strlen(sql));
	if (rt) {
		cout << sql_s << "错误信息： " << mysql_error(con) << endl;
		return false;
	}
	else
		return true;
}

// 执行预处理语句
bool CSql::prepareStmt(string sql_s, MYSQL_BIND* params)
{
	const char* sql = sql_s.c_str();
	MYSQL_STMT *stmt = mysql_stmt_init(con); //创建MYSQL_STMT句柄
	if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
	{
		cout << sql_s << "预处理语句初始化失败: " << mysql_error(con);
		return false;
	}
	mysql_stmt_bind_param(stmt, params);
	mysql_stmt_bind_result(stmt, params);
	mysql_stmt_execute(stmt);      //执行预处理
	mysql_stmt_store_result(stmt); //以便后续的mysql_stmt_fetch()调用能返回缓冲数据
	string err = mysql_stmt_error(stmt);
	mysql_stmt_close(stmt);
	if (err == ""){
		return true;
	}
	else{
		cout << "错误信息: " << err << endl;
		return false;
	}
}

// 开启自动提交事务
bool CSql::openAutoCommit()
{
	return this->sql("set autocommit=1;");
}

// 开启手动提交事务
bool CSql::openManuCommit()
{
	return this->sql("set autocommit=0;");
}

// 事务回滚
bool CSql::rollBack()
{
	return this->sql("rollback;");
}

// 事务提交
bool CSql::commit()
{
	return this->sql("commit;");
}

// 输出查询结果，并返回查询到的数据总数
unsigned int CSql::putOutRes(bool b)
{
	unsigned int t, j, count = 0;
	MYSQL_RES *res = mysql_store_result(con);
	MYSQL_ROW row;
	MYSQL_FIELD *fd;    //字段列数组
	list<string> field; //字段名队列
	
	if (b)
	{
		// 获取字段名
		for (int i = 0; fd = mysql_fetch_field(res); i++)
			field.push_back(fd->name);
		// 获取列数
		j = mysql_num_fields(res);
		// 打印字段
		for (int i = 0; i < j; i++) {
			cout << field.front() << "\t";
			field.pop_front();
		}
		cout << endl;
	}

		// 从当前结果集中获取数据，并滑向下一行，取到最后一行返回false
	while (row = mysql_fetch_row(res))
	{
		if (b)
		{
			for (t = 0; t < j; t++)
				if (row[t] == NULL)
					cout << "NULL\t";
				else
					cout << row[t] << "\t";
		    cout << endl;
	    }
		count++;
	}
	if(b)
	    cout << "查询结果总数：" << count << endl;

	// 释放结果集
	mysql_free_result(res);

	return count;
}