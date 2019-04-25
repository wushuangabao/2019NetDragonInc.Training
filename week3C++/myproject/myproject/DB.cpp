#include "pch.h"
#include "DB.h"


DB::DB()
{
}


DB::~DB()
{
}


MYSQL * DB::connect()
{
	con = mysql_init(NULL); //初始化Mysql数据库
	// 
	if (con != NULL && mysql_real_connect(con, ip, user, passwd, dbname, 3306, NULL, 0))
	{
		// 设定当前激活的数据库
		if (!mysql_select_db(con, dbname))
		{
			cout << "mysql_select_db成功!" << endl;
			con->reconnect = 1;

			// 设置中文编码
			if (mysql_real_query(con, "SET NAMES GBK;", (unsigned int)strlen("SET NAME GBK;")))
			{
				cout << "字符集设置失败: " << mysql_error(con) << endl;
				system("pause");
				exit(0);
			}
		}
	}
	else
	{
		cout << dbname << "数据库连接失败: " << mysql_error(con) << endl;
		system("pause");
		exit(0);
	}
	return con;
}