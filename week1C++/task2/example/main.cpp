#define  _CRT_SECURE_NO_WARNINGS 
#include"CString.h"
#include<iostream>
using namespace std;


void main()
{
	CNString str1("abc");
	CNString str2;
	cout << "重载 = 操作符:" << endl;
	str2 = str1;
	str2.Show();
	CNString str3("efg");
	CNString str4;
	cout << "重载 + 操作符" << endl;
	str4 = str1 + str3;
	str4.Show();
	CNString nstring1("abc");
	cout << "重载 [] 操作符:" << endl;
	cout << nstring1[0] << endl;// 则屏幕显示a
	cout << nstring1[2] << endl; // 则屏幕显示c
	cout << "重载 > 操作符:" << endl;
	if (str1>str3){
		cout << "str1>str3" << endl;
	}
	cout << "重载 < 操作符:" << endl;
	if (str1<str3){
		cout << "str1<str3" << endl;
	}
	cout << "重载 == 操作符:" << endl;
	if (str1 == str3){
		cout << "str1==str3" << endl;
	}
	system("pause");
}