#define  _CRT_SECURE_NO_WARNINGS 
#include<iostream>
using namespace std;
class CNString
{

public:
	friend CNString operator+(CNString &obj1, CNString &obj2);
	friend bool operator>(CNString &obj1, CNString &obj2);
	friend bool operator<(CNString &obj1, CNString &obj2);
	friend bool operator==(CNString &obj1, CNString &obj2);
	CNString();
	CNString(const char *myp);
	//定义一个拷贝构造函数
	CNString(const CNString& obj1);
	void Show();
	~CNString();
public:
	// "="重载操作符
	CNString& operator=(CNString &obj1)
	{
		if (this->m_p != NULL)
		{
			delete[] m_p;
			m_len = 0;
		}
		this->m_len = obj1.m_len;
		this->m_p = new char[m_len + 1];
		strcpy(m_p, obj1.m_p);
		return *this;
	}
	// "[]"重载操作符
	char& operator[](int i)//返回引用进行赋值操作
	{
		return m_p[i];
	}
protected:
private:
	char *m_p;
	int m_len;
};

