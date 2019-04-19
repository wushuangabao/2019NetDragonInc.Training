#include <winsock.h>
#include "stdafx.h"
#include <time.h>
#include "db.h"
#include "mysql.h"

#pragma comment(lib,"libmySQL.lib")

using namespace std;

/////////////////////////////////////////////
//事务处理1：创建people账户，选择actor角色
/////////////////////////////////////////////
bool DB::transc1(char* name, char* pswd, unsigned int sex, char* act)
{
	//修改数据库提交模式为0，也就是手动提交----------------------
	if (!this->sql("set autocommit=0;"))
	{
		cout << "Close autocommit failed: " << mysql_error(con) << endl;
		return false;
	}
	//开始事务处理-----------------------------------------------
	if (!this->sql("start transaction;"))
	{
		cout << "Start transaction failed: " << mysql_error(con) << endl;
		this->openAutoCommit();
		return false;
	}
	//创建账户----------------------------------------------------
	if (!CreAcc(name, pswd, sex))
	{
		if (!this->sql("rollback;"))  //事务回滚
			cout << "Rollback failed: " << mysql_error(con) << endl;
		this->openAutoCommit();
		return false;
	}
	//找到Actor中的记录，给其user字段赋值--------------------------
	string act_s = act;
	string name_s = name;
	if (this->sql("update actor set `user` = \"" + name_s + "\" where `name` = \"" + act_s + "\""))
	{
		if (this->sql("commit;"))  //事务提交
		{
			this->openAutoCommit();
			return true;
		}
		else
			cout << "Commit failed: " << mysql_error(con) << endl;
	}
	//如果失败------------------------------------------------------
	if (!this->sql("rollback;"))  //事务回滚
		cout << "Rollback failed: " << mysql_error(con) << endl;
	this->openAutoCommit();
	return false;
}

/////////////////////////////////////////////
//执行任意SQL语句
/////////////////////////////////////////////
bool DB::sql(string sql_s)
{
	char sql[400];
	strcpy(sql, sql_s.c_str());
	int rt = mysql_real_query(con, sql, strlen(sql));
	if (rt)
		return false;
	else
		return true;
}

/////////////////////////////////////////////
//插入数据
/////////////////////////////////////////////
void DB::insert(string tablename) {
	char tmp[400];
	int rt;
	//people表--------------------------------
	if (tablename == "people")
	{
		char name[16];
		char password[16];
		int a;
		cout << endl << "Enter the name: ";cin >> name;
		//todo:重名检测
		cout << "Enter the password: ";cin >> password;
		while (true) {
			cout << "Enter 1 if you are a man, 0 if you are a woman:";cin >> a;
			if (a == 1 || a == 0)
				break;
		}

		sprintf_s(tmp, "insert into people values(\"%s\",\"%s\",%d)", name, password, a);


		rt = mysql_real_query(con, tmp, strlen(tmp));
		cout << tmp << ": ";
		if (rt) {
			cout << "insert data failed!" << endl;
			const char *str = mysql_error(con);
			cout << str << endl;
		}
		else {
			cout << "insert data success!" << endl;
		}
	}
	//msg表------------------------------------
	else if (tablename == "msg")
	{
		char user[16];
		char name[16];
		char now[30];
		char text[128];
		string name_s,user_s;
		strcpy_s(now, getTime().c_str());  //时间赋值
		while (true)
		{
			cout << "Enter 1 to enter the name of actor, 2 to enter the name of user:";
			int a; cin >> a;
			if (a == 1)
			{
				cout << endl << "Enter the name: ";cin >> name_s;
				if ((user_s = userOf(name_s)) == "???")  //如果不存在name_s对应的user
					cout << "Be sure the actor's name is correct, and enter again: ";
				else
					break;
			}
			if (a == 2)
			{
				cout << endl << "Enter the name: ";cin >> user_s;
				if ((name_s = actorOf(user_s)) == "???")
					cout << "Be sure the user's name is correct, and enter again: ";
				else
					break;
			}
		}
		strcpy(user, user_s.c_str());  //user赋值
		strcpy(name, name_s.c_str());  //name(of actor)赋值

		cout << endl << "Enter the text: ";cin >> text;  //聊天内容赋值
		sprintf_s(tmp, "insert into msg values(%d,\"%s\",\"%s\",\"%s\",\"%s\")", msg_id, user, name, text, now);
		rt = mysql_real_query(con, tmp, strlen(tmp));
		cout << tmp << ": ";
		if (rt) {
			cout << "insert data failed!" << endl;
			const char *str = mysql_error(con);
			cout << str << endl;
		}
		else {
			cout << "insert data success!" << endl;
			msg_id++;
		}
	}
	else
		cout << "Error! Unkown table name." << endl;
}

/////////////////////////////////////////////
//删除数据
/////////////////////////////////////////////
void DB::delet(string tablename) {
	char tmp[400];
	int rt;
	char name[16];
	cout << "Enter the name of people: ";cin >> name;
	//todo:查询people's name是否存在

	//sprintf_s(tmp, "delete from %s where name=\"%s\"", tablename, name);//乱码bug，用下面3行代替并关闭sdl检查
	string tmp_s = "delete from " + tablename + " where name=\"" + name +"\"";
	unsigned int length = tmp_s.copy(tmp, 399);
	tmp[length] = '\0';

	rt = mysql_real_query(con, tmp, strlen(tmp));
	cout << tmp << ": ";
	if (rt) {
		cout << "Delete data failed!" << endl;
		const char *str = mysql_error(con);
		cout << str << endl;
	}
	else {
		cout << "Delete data success!" << endl;
	}
}

/////////////////////////////////////////////
//更新数据
/////////////////////////////////////////////
void DB::update(string tablename) {
	char tmp[400];
	char name[16];
	int rt;
	cout << "Enter the name of " << tablename << ": "; cin >> name;

	if (tablename == "people")
	{
		char password[16];
		cout << "Enter the new password: ";cin >> password;
		sprintf_s(tmp, "update people set `passwd` = \"%s\" where `name` = \"%s\"", password, name);
		rt = mysql_real_query(con, tmp, strlen(tmp));
		if (rt) {
			cout << "Update data failed! " << mysql_error(con) << endl;
		}
		else {
			cout << "Update data success!" << endl;
		}
	}
	else if (tablename == "actor")
	{
		char people[16];
		cout << "Enter the new people's name: ";cin >> people;
		//TODO：检查people's name是否存在。

		sprintf_s(tmp, "update actor set `user` = \"%s\" where `name` = \"%s\"", people, name);
		/*string user_s = people;
		string tmp_s = "update actor set `user` = \"" + user_s + "\" where `name`=\"" + name + "\"";
		unsigned int length = tmp_s.copy(tmp, 399);
		tmp[length] = '\0';*/

		cout << tmp << ": ";
		rt = mysql_real_query(con, tmp, strlen(tmp));
		if (rt) {
			cout << "Update data failed! " << mysql_error(con) << endl;
		}
		else {
			cout << "Update data success!" << endl;
		}
	}
}

/////////////////////////////////////////////
//查询数据
/////////////////////////////////////////////
void DB::query() {
	cout << "Table 1 (people) --------------------------" << endl;
	this->query("people");
	cout << "Table 2 (actor) ---------------------------" << endl;
	this->query("actor");
	cout << "Table 3 (msg) -----------------------------" << endl;
	this->query("msg");
}

void DB::query(string tablename) {
	int rt, count=0;
	unsigned int t;
	MYSQL_RES *res;
	char tmp[400];

	//sprintf_s(tmp, "select * from %s", tablename);//此句无法给tmp赋值。只能用下面三行代替，且要关闭sdl检查。
	string tmp_s = "select * from " + tablename;
	unsigned int length = tmp_s.copy(tmp, 399);
	tmp[length] = '\0';

	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		cout << "mysql_real_query failed!" << mysql_error(con) << endl;
		exit(0);
	}
	else
	{
		cout << tmp << ": success." << endl;
	}
	res = mysql_store_result(con); //将结果保存在res结构体中

	MYSQL_FIELD *fd;  //字段列数组
	char field[32][32];  //存字段名二维数组
	for (int i = 0;fd = mysql_fetch_field(res);i++)  //获取字段名  
		strcpy(field[i], fd->name);
	int j = mysql_num_fields(res);  // 获取列数  
	for (int i = 0;i<j;i++)  //打印字段  
		cout<< field[i] << "\t";
	cout << endl;
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		for (t = 0;t<j;t++)
			if (row[t] == NULL)
				cout << "NULL\t";
			else
				cout << row[t] << "\t";
		count++;
		cout << endl;
	}
	cout << "The datas' number is " << count << endl;
	if (tablename == "msg")
		msg_id = count + 1;
	mysql_free_result(res);  //释放结果集
}

/////////////////////////////////////////////
//连接数据库
/////////////////////////////////////////////
MYSQL * DB::connect()
{
	int rt;
	con = mysql_init((MYSQL*)0);
	if (con != NULL && mysql_real_connect(con, ip, user, passwd, dbname, 3306, NULL, 0))
	{
		if (!mysql_select_db(con, dbname))
		{
			cout << "mysql_select_db success." << endl;
			con->reconnect = 1;
			rt = mysql_real_query(con, "SET NAMES GBK;", (unsigned int)strlen("SET NAME GBK;"));//否则cmd下中文乱码
			if (rt)
			{
				cout << "mysql_real_query ZiFuJi can't be set: " << mysql_error(con) << endl;
				system("pause");
				exit(0);
			}
			else
			{
				cout << "mysql_real_query ZiFuJi is set!" << endl;
			}
		}
	}
	else
	{
		cout << "mysql_select_db failed!" << endl;
		exit(0);
	}
	return con;
}

/////////////////////////////////////////////
//析构
/////////////////////////////////////////////
DB::~DB()
{
	mysql_close(con); //释放连接
	memset(user, 0, sizeof(user));
	memset(passwd, 0, sizeof(passwd));
	memset(ip, 0, sizeof(ip));
	memset(dbname, 0, sizeof(dbname));
	msg_id = 0;
	con = NULL;
}

////////////////////////////////////////////
//私有成员函数
////////////////////////////////////////////
string DB::userOf(string actor)
{
	MYSQL_RES *res;
	char tmp[400];
	//sprintf_s(tmp, "SELECT `user` from actor WHERE `name`=\"%s\"",actor);
	string tmp_s = "SELECT `user` from actor WHERE `name`=\"" + actor + "\"";
	unsigned int length = tmp_s.copy(tmp, 399);
	tmp[length] = '\0';

	int rt = mysql_real_query(con, tmp, (unsigned int)strlen(tmp));
	if (rt)
	{
		cout << "Cannot get the user of " << actor << "! error: " << mysql_error(con) << endl;
		return "???";
	}
	res = mysql_store_result(con); //将结果保存在res结构体中
	string user;
	MYSQL_ROW row = mysql_fetch_row(res);
		if (row == NULL)
			user="???";
		else
			user=row[0];
	mysql_free_result(res);  //释放结果集
	return user;
}

string DB::actorOf(string user)
{
	MYSQL_RES *res;
	char tmp[400];
	string tmp_s = "SELECT `name` from actor WHERE `user`=\"" + user + "\"";
	unsigned int length = tmp_s.copy(tmp, 399);
	tmp[length] = '\0';

	int rt = mysql_real_query(con, tmp, (unsigned int)strlen(tmp));
	if (rt)
	{
		cout << "Cannot get the actor of " << user << "! error: " << mysql_error(con) << endl;
		return "???";
	}
	res = mysql_store_result(con); //将结果保存在res结构体中
	char actor[16];
	MYSQL_ROW row = mysql_fetch_row(res);
	if (row == NULL)
		strcpy(actor, "???");
	else
		strcpy(actor , row[0]);
	mysql_free_result(res);  //释放结果集
	return actor;
}

string DB::getTime()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %X", localtime(&t));
	return string(tmp);
}

void DB::openAutoCommit()
{
	if (!this->sql("set autocommit=1;"))
		cout << "Open autocommit failed: " << mysql_error(con) << endl;
}

bool DB::CreAcc(char* name, char* pswd, unsigned int sex)
{
	char sex_c;
	if (sex == 1)
		sex_c = 1;
	else
		sex_c = 0;

	MYSQL_STMT *stmt = mysql_stmt_init(con); //创建MYSQL_STMT句柄
	char* sql = "insert into people values(?,?,?);";
	if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
	{
		cout << "mysql_stmt_prepare failed: " << mysql_error(con);
		return false;
	}
	MYSQL_BIND params[3];
	memset(params, 0, sizeof(params));
	params[0].buffer_type = MYSQL_TYPE_STRING;
	params[0].buffer = name;
	params[0].buffer_length = strlen(name);
	params[1].buffer_type = MYSQL_TYPE_STRING;
	params[1].buffer = pswd;
	params[1].buffer_length = strlen(pswd);
	params[2].buffer_type = MYSQL_TYPE_TINY;
	params[2].buffer = &sex_c;
	params[2].buffer_length = 1;

	mysql_stmt_bind_param(stmt, params);
	mysql_stmt_bind_result(stmt, params); //用于将结果集中的列与数据缓冲和长度缓冲关联（绑定）起来
	mysql_stmt_execute(stmt);  //执行与语句句柄相关的预处理
	mysql_stmt_store_result(stmt);  //以便后续的mysql_stmt_fetch()调用能返回缓冲数据
	string err = mysql_stmt_error(stmt);
	mysql_stmt_close(stmt);
	if (err == "")  //创建账户成功
		return true;
	else  //创建账户失败
	{
		cout << "Error when create accout: " << err << endl;
		return false;
	}
}