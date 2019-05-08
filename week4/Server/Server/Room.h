#pragma once
#include <vector>
#include <list>
#include <string>
#include "Socket/json.hpp"

using namespace std;
using json = nlohmann::json;

class SocketList;
class DataSocket;
class DB;

class Room
{
public:
	Room();
	~Room();
	void CreateRoom();       //创建房间，创建服务器
	void refreshNames();     //让客户端刷新房间中所有人的名字
	void sendInfo(string s, bool toAll = true); //向客户端发送消息
	bool findName(string name);                 //查找name是否在房间

	list<string> nameInRoom; //本房间中用户名字队列

private:
	void Fresh();        //刷新
	string allName();    //房间中所有人的名字
	void putOutWords();  //显示消息
	void detectingMsg(); //监听消息
	vector<string> SeparateMsg(string str); //拆包
	bool detectingInstruct(json j); //指令检测与执行
	void checkAccount(string name, string pswd); //校验用户名、密码

	static SocketList* sockets; //本房间的Socket通信接口
	DataSocket* RecSocket;      //保存发来消息的Socket
	list<string> RecStrList;    //接收到的消息队列
	int size = 5;  //房间人数上限
	DB* db;
};