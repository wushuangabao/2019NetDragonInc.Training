#include "stdafx.h"
#include "db.h"

using namespace std;

// 获取表名
string getTName(int i)
{	
	cout << endl << "Enter 1 to the People, ";
	if(i==2)  // 聊天信息表可以增加记录
		cout << "2 to the Msg Table, 0 to exit : ";
	else if(i==4)  //角色表可以修改记录的user
		cout << "2 to the Actor Table, 0 to exit : ";
	else if(i==1)
		cout << "2 to the Actor Table, 3 to the Msg Table, 0 to exit : ";
	int j;
	cin >> j;
	if (j == 0)
		exit(0);
	else if (j == 1)
		return "people";
	else if (1 == i)  //query
	{
		if (j == 3)
			return "msg";
		else if (j == 2)
			return "actor";
	}
	else if (i == 2)  //insert
	{
		if (j == 2)
			return "msg";
	}
	else if (i == 4)  //update
	{
		if (j == 2)
			return "actor";
	}
	else
	{
		cout << "An unkown integer is input, please again.";
		getTName(i);
	}
}

bool create(DB* db);  //创建账户并选择角色

int main()
{
	DB dataBase;
	string tbname="";
	string sql;
	int i = 0;
	bool goOut = false;
	dataBase.connect();
	cout << endl;
	dataBase.query();

	while (!goOut)
	{
		cout << endl << "Enter 1 to query DB , 2 to insert data ,"
			<< " 3 to delete data , 4 to change data ,"
			<< endl << "Enter 5 to write a sql statement , "
			<< "6 to create an accout and select an actor , "
			<< "0 to exit : ";
		cin >> i;
		switch (i)
		{
		case 0:
			goOut = true;
			break;
		case 1:
			dataBase.query(getTName(i));
			break;
		case 2:
			dataBase.insert(getTName(i));
			break;
		case 3:
			dataBase.delet(getTName(i));
			break;
		case 4:
			dataBase.update(getTName(i));
			break;
		case 5:
			cout << "Please enter a SQL statement (end with ';'): " << endl;
			getline(cin, sql, ';');
			if (dataBase.sql(sql))
				cout << "Success!" << endl;
			else
				cout << "Failed!" << endl;
			break;
		case 6:
			if(create(&dataBase))  //创建账户并选择角色
				cout<< "Success!" << endl;
			else
				cout << "Failed!" << endl;
			break;
		default:
			cout << "An unkown integer is input." << endl;
		}
	}

	return 0;
}

bool create(DB* db)
{
	char name[16];
	char pswd[16];
	unsigned int sex;
	char act[16];
	cout << "Enter your name:"; cin >> name;
	//todo:重名检测
	cout << "Enter your password: "; cin >> pswd;
	while (true)
	{
		cout << "Enter 1 if you are man, 0 if you are woman: ";cin >> sex;
		if (sex == 1 || sex == 0)
			break;
	}
	cout << "You can chose an actor from the table: " << endl;
	db->query("actor");
	cout << "Enter your actor's name: "; cin >> act;
	//todo:检测act是否可用
	return db->transc1(name, pswd, sex, act);
}