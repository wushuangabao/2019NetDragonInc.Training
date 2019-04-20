#pragma once
#include "Socket/TCPSocket.h"
#include "Socket/SocketList.h"
#include "Thread/ThreadLib.h"

using namespace std;

class Chat
{
public:
	Chat();
	~Chat();

	string myName;      //自己的名字
	bool alreadyCon = false;
	void Fresh();       //刷新
	void EnterRoom();   //进入房间，创建客户端
	static void CinString(void *Receive); //输入聊天消息

	vector<string> SeparateMsg(string str);//拆包
	bool detectingInstruct(string str);    //指令检测与执行
	void putOutWords();   //输出消息
	void detectingMsg();  //检测是否收到新消息
	static SocketList* Room; //本机Socket通信接口
	list<string> RecStrList; //保存接收的消息

	string getTime();  //获取系统时间
};