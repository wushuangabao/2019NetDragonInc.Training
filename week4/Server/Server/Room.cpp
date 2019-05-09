#include <algorithm>
#include <iostream>
#include "Socket/SocketList.h"
#include "Room.h"
#include "MySQL/DB.h"

using namespace std;

SocketList* Room::sockets = NULL;

Room::Room(): RecSocket(NULL)
{
	StartSocketLib;
	db = DB::getInstance();
	//srand(GetTickCount());
}

Room::~Room() { CloseSocketLib; }

void Room::CreateRoom()
{
	sockets = new SocketList();
	Fresh();
}

void Room::Fresh()
{
	cout << allName() << endl;
	while (true)
	{
		detectingMsg();
	}
}

// 监听消息
void Room::detectingMsg()
{
	RecStrList = sockets->Listening(this,&RecSocket);
	if (RecStrList.size() != 0)
		putOutWords();
}

// 分割数据包
vector<string> Room::SeparateMsg(string str)
{
	vector<string> retStrVec;
	int pos;
	while ((pos = str.find("#end#")) != string::npos)
	{
		retStrVec.push_back(str.substr(0, pos));
		str.erase(0, pos + 5);
	}
	if (str != "")
		retStrVec.push_back(str);
	return retStrVec;
}

// 执行指令
bool Room::detectingInstruct(json j)
{
	try{
		// 处理不同的指令（参见“通讯协议文档”）
		if (j["instruct"]) {
			string str = j["str"];
			// connect指令
			if (str == "connect")
			{
				string name = j["name"],
					pswd = j["pswd"];
				checkAccount(name, pswd);
			}
			// manipulate指令
			else if (str == "manipulate")
			{
				// 数据库manipulate表增添记录

				// 广播指令
				sockets->SendToAllClient(j.dump() + "#end#");
			}
			return true;
		}
	}
	catch (exception e) 
	{
		cout << "指令解析失败！" << endl;
	}
	return false;
}

void Room::checkAccount(string name, string pswd)
{
	// 检查房间是否满员
	if (size <= nameInRoom.size())
	{
		sendInfo("The room is already full!", false);
		return;
	}
	// 查找name是否已经已经登录
	if (findName(name))
	{
		sendInfo("User \"" + name + "\" is already in the room!", false);
		return;
	}
	// 从数据库查找用户名和密码
	int v = db->checkAccount(name, pswd);
	if (v == 0) {
		sendInfo("Login successfully!", false);
		string oldName = RecSocket->userName;
		if (oldName != "")
			nameInRoom.remove(oldName);
		nameInRoom.push_back(name);
		RecSocket->userName = name;
		refreshNames();
	}
	else if (v == 1) {
		sendInfo("User name \"" + name + "\" does not exist!", false);
	}
	else if (v == 2) {
		sendInfo("Error password!", false);
	}
	else {
		sendInfo("Logon failed!", false);
	}
}

// 输出房间中所有人的名字
string Room::allName()
{
	string s = "The people in this room: ";
	if (nameInRoom.size() == 0)
		s += "No People";
	else
		for (list<string>::iterator itr = nameInRoom.begin(); itr != nameInRoom.end(); itr++)
			s = s + *itr + " ";
	return s;
}

// 刷新房间中所有人的名字（并广播给客户端）
void Room::refreshNames()
{
	sendInfo(allName());
	cout << allName() << endl;
}

// 向客户端发送一条文本
// toAll true:广播 fasle:发送给当前RecSocket
void Room::sendInfo(string s, bool toAll) {
	json j = {
		{"instruct",false},
		{"name","Server"},
		{"time",""},
		{"str",s}
	};
	if (toAll)
		sockets->SendToAllClient(j.dump() + "#end#");
	else
		RecSocket->SendData(j.dump() + "#end#");
}

// 查找name是否在房间
bool Room::findName(string name)
{
	list<string>::iterator iter = find(nameInRoom.begin(), nameInRoom.end(), name);
	if (iter != nameInRoom.end())
		return true;
	else
		return false;
}

// 显示、处理消息
void Room::putOutWords()
{
	json j;
	for (list<string>::iterator itr = RecStrList.begin(); itr != RecStrList.end(); itr++)
	{
		vector<string> msgVector = SeparateMsg(*itr);
		for (vector<string>::iterator it = msgVector.begin(); it != msgVector.end(); it++)
		{
			if (*it == "")
				break;
			// 显示消息
			cout << *it << endl;
			// 解析消息
			try {
				j = json::parse(*it);
				// 判断、处理指令
				if (!detectingInstruct(j))
				{
					// case:不是指令，是普通聊天消息
					db->createChatRecord(j["name"], j["str"]);
					sockets->SendToAllClient(*it + "#end#");
				}
			}
			catch (exception e) {
				cout << "消息解析失败！" << endl;
			}
		}
	}
}