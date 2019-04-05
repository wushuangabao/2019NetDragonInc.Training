#include "stdafx.h"
#include "iostream"

using namespace std;

#define MAX 11              //int类型最大不会超过10位数
#define MAX_INT 2147483647

/***********************************itostr************************************
Author:    无双BaOY_WHA
iput:      整数n，范围0至MAX_INT。可选参数：字符类型指针string。
output:    字符串，内容为整数n的值，如果写了string参数，则后面再加上string内容。
*****************************************************************************/
char* itostr(int n, char* string=new char[MAX])
{
	int n1 = n % 10;
	int n2 = n / 10;
	char c[MAX] = { n1 + '0','\0' };  //n1是个位数，直接转换为char*类型的c
	if (n2 != 0)
	{
		char* string = itostr(n2, c);  //递归调用自身
		//拼接字符串：
		char* t = c;
		char* s = string;
		while (*s)s++;
		while (*t)*s++ = *t++;
		*s = '\0';
		return string;
	}
	else
	{
		char* st = c;
		return st;
	}
}

//////////////////////////////////////////////////
//Main Function
//////////////////////////////////////////////////
int main()
{
	int n = 0;
	char* string = NULL;
	cout << "Please input an integer(1-" << MAX_INT << ", if not in this range, system will be damaged.)" << endl;
	cin >> n;
	while (true)
	{
		if (n > MAX_INT)
		{
			cout << "It's too big!" << endl;
			cout << "Please input an integer(1-" << MAX_INT << ") again:";
			cin >> n;
		}
		else if (n < 0)
		{
			cout << "It must be a positive integer!" << endl;
			cout << "Please input an integer(1-" << MAX_INT << ") again:";
			cin >> n;
		}
		//todo:防止输入小数或过大的数字时时陷入死循环
		string = itostr(n);
		char c[MAX];
		//cout << "string=";//调试发现任何cout都会改变string指针所指的内容
		for (int i = 0;i < MAX;i++)
		{
			c[i] = *(string + i);
			if (c[i] == '\0')break;
		}
		cout<< "string=" << c << endl;
		cout << "Input 0 to exit." << endl;
		cout << "Input other numbers to continue." << endl;
		cin >> n;
		if (n == 0)return 0;
	}
    return 0;
}

