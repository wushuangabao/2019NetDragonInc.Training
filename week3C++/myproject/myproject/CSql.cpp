#include "pch.h"
#include "CSql.h"


CSql::CSql()
{
	// 初始化MySql数据库
	pConn = mysql_init(NULL);

	// 连接数据库
	MYSQL* p = (MYSQL*)pConn;
	if (mysql_real_connect(p, "localhost", "root", "", "chat", 0, NULL, 0))
	    std::cout << "连接数据库成功!" << std::endl;
	else{
		std::cout << "无法连接数据库! 错误信息: " << mysql_error(p) << std::endl;
		//MessageBox(NULL, L"无法连接数据库!", L"Prompt", 0);
		system("pause");
		exit(0);
	}
}


CSql::~CSql()
{
	delete pConn;
}
