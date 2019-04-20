#pragma once
#include <vector>
#include <list>
#include <string>

using namespace std;

class SocketList;
class DataSocket;

class Chat
{
public:
	Chat();
	~Chat();

	void Fresh();       //刷新
	void CreateRoom();  //创建房间，创建服务器
	string allName();   //房间中所有人的名字
	list<string> nameInRoom;

	vector<string> SeparateMsg(string str);//拆包
	bool detectingInstruct(string str);    //指令检测与执行
	void putOutWords();   //显示聊天消息
	void detectingMsg();  //监听新的消息

	static SocketList* sockets; //本机Socket通信接口
	DataSocket* RecSocket;   //保存发来消息的Socket
	list<string> RecStrList; //保存接收的消息
};