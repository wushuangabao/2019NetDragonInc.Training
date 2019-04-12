#include <iostream>
#include "CClient.h"

using namespace std;

int main()
{
	CClient cliet;
	//连接服务器
	if (cliet.ConnectServer())
	{
		//开启发送接收线程
		cliet.CreateSendAndRecvThread();
		string use = "";
		cout << "输入用户名：" << endl;
		//cin >> use;
		getline(cin, use, '\n');
		string str = "";
		while (true)
		{
			log_packet payload;

			payload.set_log_len(10);
			payload.set_log_level("DEBUG");
			payload.set_send_user_name(use);
			payload.set_packet_rec_ip("127.0.0.1");
			payload.set_log_msg("What shall we say then");

			cout << "请输入要发送的数据： " << endl;
			//cin >> str;
			getline(cin, str, '\n');
			if (str == "q")
			{
				exit(0);
			}
			payload.set_log_msg(str);
			//数据序列化
			int siz = payload.ByteSize() + 4;
			char *pkt = new char[siz];
			google::protobuf::io::ArrayOutputStream aos(pkt, siz);
			CodedOutputStream *coded_output = new CodedOutputStream(&aos);
			coded_output->WriteVarint32(payload.ByteSize());
			payload.SerializeToCodedStream(coded_output);
			//发送数据
			cliet.sendData(cliet.sClient, pkt, siz);
			cin.clear();
			cin.sync();
		}
	}
	
	system("pause");
	return 0;
}