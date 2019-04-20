#include <time.h>
#include <iostream>
#include "Socket/json.hpp"
#include "Chat.h"

using namespace std;
using json = nlohmann::json;

SocketList* Chat::Room = NULL;

Chat::Chat()
{
	StartSocketLib;
	srand(GetTickCount());
}

Chat::~Chat() { CloseSocketLib; }

void Chat::EnterRoom()
{
	cout << "input your name:";
	cin >> myName;
	Room = new SocketList();
	Fresh();
}

void Chat::Fresh()
{
	ThreadLib::ThreadID CinThread;
	string *str = new string;
	while (true)
	{
		CinThread = ThreadLib::Create(CinString, (void*)str);
		while (true)
		{
			detectingMsg();
			if (*str != "")
			{
				json j = {
					{"name",myName},
					{"time",getTime()},
					{"instruct",false},
					{"str",*str}
				};
				Room->SendToServer(j.dump() + "#end#");
				*str = "";
				break;
			}
			Sleep(100);
		}
	}
	delete str;
}

void Chat::CinString(void *Receive)
{
	string *Result = static_cast<string*>(Receive);
	*Result = "";
	cin >> *Result;
}

void Chat::detectingMsg()
{
	RecStrList = Room->Listening();
	if (RecStrList.size() != 0)
	{
		putOutWords();
		cout << endl << "input message:" << endl;
	}
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

// 监听指令
bool Chat::detectingInstruct(string rec_str)
{
	if (rec_str=="")
		return true;
	json j = json::parse(rec_str);
	if (j["instruct"] == true)
	{
		string str = j["str"];
		if (str == "Connected" && !alreadyCon)
		{
			json j = {
				{"instruct",true},
				{"str","connect"},
				{"name",myName}
			};
			Room->SendToServer(j.dump() + "#end#");
			alreadyCon = true;
		}
		else if (str == "ReConnect")
		{
			json j = {
				{"instruct",true},
				{"str","connect"},
				{"name",myName}
			};
			Room->SendToServer(j.dump() + "#end#");
		}
		return true;
	}
	return false;
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
				json j = json::parse(*it);
				cout << j["name"] << " " << j["time"] << " : " << j["str"] << endl;
			}
		}
	}
}

string Chat::getTime()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%X", localtime(&t));
	return string(tmp);
}