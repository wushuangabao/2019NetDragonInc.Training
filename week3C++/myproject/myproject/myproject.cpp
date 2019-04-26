#include "pch.h"
#include "DB.h"
#pragma comment(lib,"libmySQL.lib")

using namespace std;

int main()
{
	// 获取单例对象
	DB* db = DB::getInstance();

	// 创建用户
	string name;
	cout << endl << "输入用户名：";
	cin >> name;
	if (db->createAccount(name))
		cout << "用户创建成功!" << endl;
	else
		cout << "用户创建失败!" << endl;

	// 输出所有表
	db->printAllTable();

	// 修改用户名
	string newName;
	cout << endl << "修改用户名，新的用户名为：";
	cin >> newName;
	if (db->changeUserName(newName,name))
		cout << "用户名修改成功!" << endl;
	else
		cout << "用户名修改失败!" << endl;

	// 输出所有表
	db->printAllTable();

	// 删除用户数据
	cout << endl << "删除用户，用户名为：";
	cin >> name;
	if (db->deleteUser(name))
		cout << "用户删除成功!" << endl;
	else
		cout << "用户删除失败!" << endl;

	// 输出所有表
	db->printAllTable();

	// 关闭数据库连接
	system("pause");
	delete db;

	system("pause");
	return 0;
}