#include"CServer.h"

int main()
{
	CServer ser;
	ser.WaitForClient();
	system("pause");
	return 0;
}