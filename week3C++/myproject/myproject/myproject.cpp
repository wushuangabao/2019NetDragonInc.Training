#include "pch.h"
#pragma comment(lib,"libmySQL.lib")

using namespace std;

int main()
{
	MYSQL *pConn;                    //定义一个结构体指针
	pConn = mysql_init(NULL);        //回调函数，用来初始化Mysql数据库
	//第2、3、4、5参数的意思分别是：服务器地址、用户名、密码、数据库名，第6个为mysql端口号（0为默认值3306）
	if (!mysql_real_connect(pConn, "localhost", "root", "", "chat", 0, NULL, 0))
	{
		printf("无法连接数据库:%s", mysql_error(pConn));
		return false;
	}
	else
	{
		cout << "连接数据库成功" << endl;
	}
	mysql_query(pConn, "set names gbk");//设置一下编码问题

	if (mysql_query(pConn, "select * from user"))  //系统API，用来查询数据
	{
		printf("查询失败:%s", mysql_error(pConn));
		return false;
	}
	else {
		cout << "查询成功" << endl;
	}

	MYSQL_RES *result = mysql_store_result(pConn);            //这里是将查询到的结果集存下来，放到result中去
	MYSQL_ROW row;                            //return data as array of strings 返回一个类似数据集合的变量
	while (row = mysql_fetch_row(result))                // 从当前结果集result中获取数据，并且滑向下一行，取到最后一行返回false
	{
		printf("%s %s\n", row[0], row[1]);    //依次输出当前数据的内容
	}
	system("pause");
	mysql_free_result(result);                                                                    //释放结果集
	mysql_close(pConn);                                                                            //关闭当前指针对象
	return 0;

}