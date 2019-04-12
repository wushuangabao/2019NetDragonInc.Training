#include <stdio.h>
#include <tchar.h>
#include "Socket/TCPSocket.h"
#include "Socket/SocketList.h"
#include "Thread/ThreadLib.h"

#pragma comment( lib, "Lib\\libprotobuf-lited.lib" )
#pragma comment( lib, "Lib\\libprotobufd.lib" )
#pragma comment( lib, "Lib\\libprotocd.lib" )

#include <iostream>
#include <conio.h>
#include <time.h>
#include <algorithm>

using namespace std;

class Chat
{
public:
	Chat();
	~Chat();
	//名字处理--------------------------------------------
	string SetName();  //设置名字
	void ActivateAllName();  //激活所有名字
	void DeleteName(string name); //防止同名
	string myName;//保存自己的聊天名字
	void ShowName();//显示房间中所有人的名字
	vector<string> AllName;//所有可用的名字列表
	vector<string> NameInRoom;//出现在房间中的名字
	int MaxName;//当前可用名字的最大数
	//消息处理---------------------------------------------
	static void CinString(void *Receive);//输入
	int Menu();  //菜单
	void CreateRoom();  //创建房间，创建服务器
	void EnterRoom();  //进入房间，创建客户端
	void Fresh();  //刷新
	vector<string> SeparateMsg(string str);//拆包
	bool detectingInstruct(string str);  //指令检测与执行
	void putOutWords();  //输出
	void detectingMsg();  //检测是否收到新消息
	static SocketList* Room;//本机Socket通信接口
	DataSocket* RecSocket;//保存发来消息的Socket
	list<string> RecStrList;  //保存接收的消息
	bool isServer;//是否为服务器
	string getTime();  //获取系统时间
};


//全局----------------------------------------------------------
SocketList* Chat::Room = NULL;
const int Max_Name = 7;  //每个聊天室的人数上限，可以改
//----------------------------------------------------------------


int main()
{
	Chat Start;
	Start.Menu();
	return 0;
}

Chat::Chat() :MaxName(Max_Name), RecSocket(NULL)
{
	StartSocketLib;
	srand(GetTickCount());
}

Chat::~Chat() { CloseSocketLib; }

int Chat::Menu()
{
	cout << "Enter 1 to be a server." << endl;
	cout << "Enter 2 to be a client." << endl;
	while (true)
	{
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			CreateRoom();
			break;
		}
		else if (select == 2)
		{
			EnterRoom();
			break;
		}
		else
		{
			cout << "Error! Please try again." << endl;
		}
	}
	return 0;
}

void Chat::CreateRoom()
{
	isServer = true;
	Room = new SocketList(true);
	ActivateAllName();
	DeleteName(myName = SetName());
	NameInRoom.push_back(myName);
	Fresh();
}

void Chat::EnterRoom()
{
	isServer = false;
	cout << "Please enter the IP with which you want to connect:";
	string RoomIp;
	cin >> RoomIp;
	Room = new SocketList(false, RoomIp);
	Fresh();
}

void Chat::CinString(void *Receive)
{
	string *Result = static_cast<string*>(Receive);
	*Result = "";
	cin >> *Result;
}

void Chat::detectingMsg()
{
	RecStrList = Room->Listening(&RecSocket);
	if (RecStrList.size() != 0)
	{
		putOutWords();
	}
}

void Chat::Fresh()
{
	ThreadLib::ThreadID CinThread;
	string *str = new string;
	if(isServer)
		ShowName();
	while (true)
	{
		CinThread = ThreadLib::Create(CinString, (void*)str);
		while (true)
		{
			detectingMsg();
			if (*str != "")
			{
				chat::data proto_data;
				/*proto_data.set_str("(" + getTime() + "):" + *str);
				proto_data.set_name(myName);
				proto_data.set_ins("");//这种发送聊天消息的方式有bug*/
				proto_data.set_ins(myName + "(" + getTime() + "):" + *str);
				proto_data.SerializeToString(str);
				if (isServer)
				{
					RecStrList.push_back(*str);
					putOutWords();
				}
				Room->Send(*str + "#end#");
				*str = "";
				break;
			}
			Sleep(200);
		}
	}
	delete str;
}

vector<string> Chat::SeparateMsg(string str) //分割不同的protobuf数据包
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

bool Chat::detectingInstruct(string rec_str)  //监听指令
{
	chat::data rec_data;
	rec_data.ParseFromString(rec_str);
	string ins = rec_data.ins();
	chat::data proto_data;  // 用于发送protobuf数据
	string *protoData=NULL;
	protoData = new string;

	//protobuf实现
	if (ins == "Connected")  //如果收到“连接”请求
	{
		if (isServer && RecSocket != NULL)  //如果是在服务器
		{
			if (AllName.size() == 0)
			{
				proto_data.set_ins("NoName");  //返回聊天室已满的信息
				proto_data.SerializeToString(protoData);
				RecSocket->SendData(*protoData + "#end#");
			}
			string newName = SetName();  //设置新的名字
			NameInRoom.push_back(newName);
			ShowName();
			proto_data.set_ins("UpdateNameInRoom");  //更新NameInRoom表
			for (vector<string>::iterator itr = NameInRoom.begin();itr != NameInRoom.end();itr++)
				proto_data.add_nameinnumber(*itr);
			proto_data.SerializeToString(protoData);
			Room->Send(*protoData + "#end#");
			proto_data.set_ins("GetName");  //发送名字给客户端
			proto_data.set_name(newName);
			proto_data.clear_nameinnumber();
			proto_data.SerializeToString(protoData);
			RecSocket->SendData(*protoData + "#end#");
			proto_data.clear_name();
		}
		delete protoData;
		return true;
	}
	else if (ins == "CheckOnline")
	{
		proto_data.set_ins("DisableName");
		proto_data.set_str(myName);
		proto_data.SerializeToString(protoData);
		Room->Send(*protoData + "#end#");
		delete protoData;
		return true;
	}
	else if (ins == "DisableName" && isServer)
	{
		DeleteName(proto_data.str());
		delete protoData;
		return true;
	}
	else if (ins == "NoName")
	{
		MessageBox(NULL, L"There are already too many people!", L"Prompt", 0);
		exit(0);
		delete protoData;
		return true;
	}
	else if (ins == "UpdateNameInRoom")
	{
		NameInRoom.clear();
		int size = rec_data.nameinnumber_size();
		for (int i=0;i!=size;++i)
			NameInRoom.push_back(rec_data.nameinnumber(i));
		ShowName();
		delete protoData;
		return true;
	}
	else if (ins == "GetName")
		{
			myName = rec_data.name();
			delete protoData;
			return true;
		}
	delete protoData;
	return false;
}

void Chat::ShowName()
{
	cout << "The people in this chat room: ";
	for (vector<string>::iterator itr = NameInRoom.begin(); itr != NameInRoom.end(); itr++)
	{
		cout << *itr << " ";
	}
	cout << endl << "Now you can type words to chat." << endl;
}

void Chat::putOutWords()
{
		bool instruct;

		//protobuf实现
		for (list<string>::iterator itr = RecStrList.begin();itr != RecStrList.end();itr++)
		{
			vector<string> msgVector = SeparateMsg(*itr);
			for (vector<string>::iterator it = msgVector.begin();it != msgVector.end();it++)
			{
				if (!(instruct = detectingInstruct(*it)))  //分析指令，如果是指令，直接执行，否则返回false
				{
					chat::data proto_data;
					proto_data.ParseFromString(*it);
					/*string strInIns = proto_data.ins();
					if (strInIns != "")
						proto_data.ParseFromString(strInIns);*/
					string s = proto_data.ins();
					//笨办法排除前置乱码的bug
					string ss = s.substr(0, 1);
					while (ss!="" && ss != "T" && ss != "J" && ss != "B") //Name的首字母
					{
						s.erase(0, 1);
						ss = s.substr(0, 1);
					}
					if (s != "") {
						cout << s << endl;
					}
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

string Chat::SetName()
{
	int num = rand() % MaxName;
	string name = AllName[num];
	AllName.erase(find(AllName.begin(), AllName.end(), name));
	return name;
}

void Chat::ActivateAllName()
{
	const string nameArr[Max_Name] = { "Tom","Jane","Jack","Ben","Toby","Tony","Jenny" };//名字列表，改动会影响putOutWords()函数
	for (int i = 0; i != Max_Name; i++)
		AllName.push_back(nameArr[i]);
}

void Chat::DeleteName(string name)
{
	vector<string>::iterator itr = find(AllName.begin(), AllName.end(), name);
	if (itr != AllName.end())
		AllName.erase(itr);
	MaxName--;
}