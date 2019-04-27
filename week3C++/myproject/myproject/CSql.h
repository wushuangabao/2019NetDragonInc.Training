#pragma once

class DB;

class CSql
{
private:
	DB* db;     //数据库
	MYSQL* con; //连接对象

public:
	CSql(DB* db);
	~CSql();

	// 执行一条sql语句
	bool sql(std::string sql_s);

	// 执行预处理语句
	bool prepareStmt(std::string sql_s, MYSQL_BIND* params);

	// 开启自动提交事务
	bool openAutoCommit();

	// 开启手动提交事务
	bool openManuCommit();

	// 事务回滚
	bool rollBack();

	// 事务提交
	bool commit();

	/**
	 * @brief 处理查询的结果
	 *
	 * @param b 是否输出到屏幕
	 * @return 查询到的数据总数
	 */
	unsigned int putOutRes(bool b = true);
};