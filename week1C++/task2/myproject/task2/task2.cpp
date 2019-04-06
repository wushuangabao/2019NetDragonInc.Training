#include <iostream>

using namespace std;

////////////////////////////
// CNString
////////////////////////////
class CNString
{
private:
	int len;  //包括'\0'
	char *str;

public:
	CNString();
	~CNString();
	CNString(const char* const s);
	CNString(const CNString& s);

	CNString& operator=(const CNString& s);
	friend CNString operator+(const CNString& s1, const CNString& s2);
	char operator[](int l)const;
	friend bool operator<(const CNString& s1, const CNString& s2);
	friend bool operator>(const CNString& s1, const CNString& s2);
	friend bool operator==(const CNString& s1, const CNString& s2);

	int getLen()const { return len; }
	const char* getStr()const { return str; }
};

// 默认构造
CNString::CNString()
{
	len = 0;
	str = new char[1];
	str[0] = '\0';
}

// 析构
CNString::~CNString()
{
	delete[] str;
	len = 0;
}

// 用char型常量的指针常量来构造
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

// 拷贝构造
CNString::CNString(const CNString &rs)
{
	len = rs.getLen();
	str = new char[len + 1];
	for (int i = 0; i < len; i++) {
		str[i] = rs.str[i];
	}
	str[len] = '\0';
}

// 重载=运算符
CNString& CNString::operator=(const CNString& rs)
{
	delete[] str;  //重新创建str
	len = rs.getLen();
	str = new char[len + 1];
	for (int i = 0; i < len; i++)
	{
		str[i] = rs.str[i];
	}
	str[len] = '\0';
	return *this;
}

CNString operator+(const CNString& s1, const CNString& s2)
{
	int l1 = s1.getLen(),
		l2 = s2.getLen(),
		l = l1 + l2;
	char* t = new char[l + 1];
	for (int i = 0; i < l1; i++)
		*(t + i) = s1.str[i];
	for (int i = 0; i < l2; i++)
		*(t + l1 + i - 1) = s2.str[i];
	t[l] = '\0';
	CNString st(t);
	delete t;
	return st;
}

char CNString::operator[](int l)const
{
	if (l > len)
	{
		cout << "The input len is bigger than CNString's len." << endl;
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

////////////////////////////
// Main
////////////////////////////
int main()
{
	CNString str1;
	CNString str2("abcd");
	CNString str3(str2);
	cout << "str1:" << str1.getStr() << endl;
	cout << "str2:" << str2.getStr() << endl;
	cout << "str3(str2):" << str3.getStr() << endl;

	str1 = str2;
	cout << "str1=str2, str1:" << str1.getStr() << endl;
	cout << "str1+str2:" << (str1+str2).getStr() << endl;

	cout << "str3[0]=" << str3[0] << endl;
	cout << "str3[1]=" << str3[1] << endl;
	cout << "str3[5]=" << str3[5] << endl;

	cout << "str1>\"aaa\"? " << (str1 > CNString("aaa")) << endl;
	cout << "str1<\"aaa\"? " << (str1 < CNString("aaa")) << endl;
	cout << "str1==\"abcd\"? " << (str1 == CNString("abcd")) << endl;

	int i;
	cout << "Input any integer to quit." << endl;
	cin >> i;

	return 0;
}

