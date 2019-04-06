#include <iostream>

using namespace std;

#define MAX_STR 11 //int类型最大不会超过10位数

////////////////////////////////////////////////
// input:n       int类型，范围0至MAX_INT
// input:string  char*类型,存放字符串
// output:       char*类型，将int转换为string
////////////////////////////////////////////////
char* itostr(int n, char* string)
{
	// 字符串的长度
	static int length = 0;

	// 记录当前递归的层数
	static int static_i = 0;
	static_i++;
	int current_i = static_i;

	// 处理负数
	if (n < 0) {
		n = -n;
		*string = '-';
		length++;
	}

	// 获取个位上的数字
	int n1 = n % 10;

	// 递归把高位数字写进string
	if (n != n1)
		itostr(n / 10, string);

	// 把个位数写进string
	*(string + length) = n1 + '0';
	length++;

	// 善后处理
	// 递归到了最后一层时
	if (n == n1)
		*(string + length) = '\0';
	// 递归结束，返回到了表层时
	if (current_i == 1) {
		length = 0;
		static_i = 0;
	}
	
	return string;
}

//////////////////////////////////////////////////
// Main Function
// 错误：输出结果是"001"，原因是递归函数中string赋值和调用自身的顺序
//////////////////////////////////////////////////
int main()
{
	int n;
	char* string = new char[MAX_STR];

	while (true) {
		for (int i = 0; i <= MAX_STR; i++)
			*(string + i) = 0;
		cout << "请输入int类型的整数：";
		cin >> n;
		cout << "你输入的数字是：" << itostr(n,string) << endl << endl;
	}

	delete string;
	return 0;
}
