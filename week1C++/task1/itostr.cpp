#include "stdafx.h"
#include "itostr.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

char * itostr(int n, char * string)
{
	//字符数组下标
	static int i = 0;
	
	//判断是否负数
	if (n < 0)
	{
		string[i] = '-';
		n = abs(n);
		i++;
	}

	//递归将每个位数赋值到字符串
	if (n/10) 
	{
		itostr(n/10, string);
	}

	string[i] = n % 10 + '0';
	i++;
	string[i] = '\0';

	return string;
}

void itostrTest()
{
	char str[30];
	int n;
	printf("┌─────────────\n");
	printf("│Test1：整数转字符串 \n");
	printf("├─────────────\n");

	printf("│-> 请输入一个整数：");
	scanf_s("%d", &n);
	printf("│\n");
	
	printf("│   输入整数为：%d\n",n);
	printf("│   执行itostr(%d,str);\n", n);
	itostr(n, str);
	printf("│   输出字符串str：%s\n", str);
	printf("│\n");
	printf("└─────────────\n");
	
	system("Pause");
}
