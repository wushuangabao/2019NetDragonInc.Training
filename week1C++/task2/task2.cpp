// task2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;

class CNString
{
public:
	CNString();
	~CNString();
	CNString(const char* const s);
	CNString(const CNString& s); //复制构造函数
	CNString& operator=(const CNString& s);
	friend CNString operator+(const CNString& s1, const CNString& s2);
	char& operator[](int l);
	char operator[](int l)const;  //用于常量的[]运算，不能对对象内部成员进行修改
	friend bool operator<(const CNString& s1, const CNString& s2);
	friend bool operator>(const CNString& s1, const CNString& s2);
	friend bool operator==(const CNString& s1, const CNString& s2);

	int getlen()const { return len; }
	const char* getstr()const{ return str; }
private:
	int len;  //包括'\0'
	char *str;
};

CNString::CNString()
{
	len = 0;
	str = new char[1];
	str[0] = '\0';
}

CNString::~CNString()
{
	delete [] str;
	len = 0;
}
 
CNString::CNString(const char* const s)
{
	if (s == NULL) {
		len = 0;
		str = new char[1];
		str[0] = '\0';
		if (str == NULL) return;
		else cout << "Error! The input string is NULL." << endl;
	}
	else {
		len = strlen(s) + 1;
		str = new char[len];
		strcpy_s(str, len, s);
	}
}

CNString::CNString(const CNString &rs)
{
	len = rs.getlen();
	str = new char[len + 1];
	for (int i = 0;i < len; i++) {
		str[i] = rs.str[i];
	}
	str[len] = '\0';
}

CNString& CNString::operator=(const CNString& rs)
{
	delete [] str;  //重新创建str
	len = rs.getlen();
	str = new char[len + 1];
	for (int i = 0; i < len; i++) 
	{
		str[i] = rs.str[i];  
	}
	str[len] = '\0';
	return *this;
}

CNString operator+(const CNString& s1,const CNString& s2)
{
	int l1 = s1.getlen();
	int l2 = s2.getlen();
	int l = l1 + l2;
	char* t = new char[l + 1];
	for (int i = 0; i < l1 ; i++)
	{
		*(t+i) = s1.str[i];
	}
	for (int i = 0; i < l2 ; i++)
	{
		*(t+l1+i-1) = s2.str[i];
	}
	t[l] = '\0';
	CNString st(t);
	delete t;
	return st;
}

char& CNString::operator[](int l)
{
	if (l > len)
	{
		cout << "The input len is bigger than CNString's len." << endl;
		return str[len];
	}
	else return str[l];
}

char CNString::operator[](int l)const
{
	if (l > len)
	{
		//cout << "The input len is bigger than CNString's len." << endl;
		return str[len];
	}
	else return str[l];
}

bool operator<(const CNString&str1, const CNString &str2)
{
	if (strcmp(str1.str, str2.str) < 0) return true;
	else return false;
}

bool operator>(const CNString&str1, const CNString &str2)
{
	if (strcmp(str1.str, str2.str) > 0) return true;
	else return false;
}

bool operator==(const CNString&str1, const CNString &str2)
{
	if (strcmp(str1.str, str2.str) == 0) return true;
	else return false;
}


int main()
{
	CNString str1;
	CNString str2(str1); 
	CNString str3("WHA is TianCai."); 
	cout << "str2=" << str2.getstr() << endl;
	cout << "str3=" << str3.getstr() << endl;

	CNString str4(str3); 
	cout << "str4=" << str4.getstr() << endl;

	CNString str5;
	str5 = str4;
	cout << "str5=" << str5.getstr() << endl;

	CNString str6 = str4 + str5;
	cout << "str6=" << str6.getstr() << endl;

	CNString str7("abc");
	cout << "str7[0]=" << str7[0] << endl;
	cout << "str7[1]=" << str7[1] << endl;
	cout << "str7[4]=" << str7[4] << endl;

	CNString str8("string1");
	CNString str9("string2");
	bool b = str8 > str9;
	cout << "str8>str9?\n" << b << endl;

	int i;
	cout << "Input any integer to quit." << endl;
	cin >> i;

	return 0;
}

