#include <time.h>
#include <iostream>
#include <algorithm>
#include "Socket/SocketList.h"
#include "Socket/json.hpp"
#include "Chat.h"

using namespace std;
using json = nlohmann::json;

SocketList* Chat::sockets = NULL;

Chat::Chat(): RecSocket(NULL)
{
	StartSocketLib;
	srand(GetTickCount());
}

Chat::~Chat() { CloseSocketLib; }

void Chat::CreateRoom()
{
	sockets = new SocketList(true);
	Fresh();
}

void Chat::Fresh()
{
	cout << allName() << endl;
	while (true)
	{
		detectingMsg();
	}
}

// 监听消息
void Chat::detectingMsg()
{
	RecStrList = sockets->Listening(this,&RecSocket);
	if (RecStrList.size() != 0)
		putOutWords();
}

// 分割数据包
vector<string> Chat::SeparateMsg(string str)
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
bool Chat::detectingInstruct(string rec_str)
{
	if (rec_str == "")
		return true;
	json j = json::parse(rec_str);
	if (j["instruct"] == true) {
		string str = j["str"];
		if (str == "connect")
		{
			nameInRoom.push_back(j["name"]);
			json j2 = {
				{"instruct",false},
				{"name","Server"},
				{"time",""},
			    {"str",allName()}
			};
			sockets->SendToAllClient(j2.dump() + "#end#");
			cout << allName() << endl;
		}
	}
	return false;
}

string Chat::allName()
{
	string s = "The people in this chat room: ";
	if (nameInRoom.size() == 0)
		s += "No People";
	else
		for (list<string>::iterator itr = nameInRoom.begin(); itr != nameInRoom.end(); itr++)
			s = s + *itr + " ";
	return s;
}

void Chat::putOutWords()
{
	bool instruct;
	for (list<string>::iterator itr = RecStrList.begin(); itr != RecStrList.end(); itr++)
	{
		vector<string> msgVector = SeparateMsg(*itr);
		for (vector<string>::iterator it = msgVector.begin(); it != msgVector.end(); it++)
		{
			if (!(instruct = detectingInstruct(*it)))
			{
				cout << *it << endl;
			}
		}
	}
}