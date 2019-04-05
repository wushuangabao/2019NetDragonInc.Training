#include "iostream"

using namespace std;

#define MAX_STR 11              //int类型最大不会超过10位数
#define MAX_INT 2147483647

////////////////////////////////////////////////
// input:     int类型，范围0至MAX_INT。
// input:     char*类型
// output:    char*类型，内容为整数n的值
////////////////////////////////////////////////
char* itostr(int n, char* string)
{
	// string的长度
	static int length = 0;

	// 处理负数
	if (n < 0) {

	}

	// 获取个位上的字符c
	int n1 = n % 10;
	char c = n1 + '0';
	*(string + length) = c;

	length++;

	// 判断递归是否到达最后一步
	if (n1 == n) {
		*(string + length) = '\0';
		return string;
	}
	else
		return itostr(n / 10, string);

}

//////////////////////////////////////////////////
// Main Function
// 错误：输出结果是"001"，原因是递归函数中string赋值和调用自身的顺序
//////////////////////////////////////////////////
int main()
{
	int n;
	char* string = itostr(100, new char);
	cout << string << endl;
	cin >> n;

	return 0;
}
