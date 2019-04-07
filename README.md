这是一个有关**我参加19年网龙公司线上训练营**的项目，将在一个月的时间内，通过完成一个个**阶段性任务**，快速入门C++和U3D。

这份文档会记录所有的任务（分为C++和Unity3D两部分），目前更新至第一阶段。

**记住：**在做任务中遇到问题，通常的解决途径是**搜索引擎**。搜索，并不是为了去copy一个现成的解决方案，而主要是为了去**理解方案背后的原理**。

友情链接：

- 菜鸟教程的[C++文档](http://www.runoob.com/cplusplus/cpp-tutorial.html)，专为初学者打造
- 参加18年C++训练营时[我做的笔记整理](https://wushuangabao.github.io/Cpp/C++%E5%BC%80%E5%8F%91%E5%85%A5%E9%97%A8%E7%B3%BB%E5%88%97_index.html)
- 微软Visual Studio的[C++语言reference](https://docs.microsoft.com/zh-cn/cpp/cpp/cpp-language-reference)

# 1. 目录


- [1. 目录](#1-目录)
- [2. C++](#2-c)
    - [2.1. 语言基础](#21-语言基础)
        - [2.1.1. 题目](#211-题目)
            - [2.1.1.1. 题目1](#2111-题目1)
            - [2.1.1.2. 题目2](#2112-题目2)
            - [2.1.1.3. 题目3](#2113-题目3)
            - [2.1.1.4. 题目4](#2114-题目4)
            - [2.1.2. 任务提交](#212-任务提交)
- [3. U3D](#3-u3d)
    - [3.1. Csharp](#31-csharp)
        - [3.1.1. 题目](#311-题目)
            - [3.1.1.1. 内容要求](#3111-内容要求)
            - [3.1.1.2. 技能要求](#3112-技能要求)
            - [3.1.1.3. 设计文档要求](#3113-设计文档要求)
        - [3.1.2. 诚信要求](#312-诚信要求)
            - [3.1.3. 提交清单](#313-提交清单)



# 2. C++

这一部分任务属于C++。

## 2.1. 语言基础

![阶段一任务卡片图](https://wushuangabao.github.io/img/netdragon/c1.png)

### 2.1.1. 题目

#### 2.1.1.1. 题目1
编写递归函数char *itostr (int n,char *string)，该函数将整数n转换为十进制表示的字符串。（提示：使用递归方法）（15分）

#### 2.1.1.2. 题目2
编码实现字符串类CNString，该类有默认构造函数、类的拷贝函数、类的析构函数及运算符重载，需实现以下“=”运算符、“+”运算、“[]”运算符、“<”运算符及“>”运算符及“==”运算符（备注：可以用strcpy_s, strcat_s，但禁用STL及String类），以下为各个运算符的运算效果的详细说明（35分）

a)	字符串“=”重载运算符

    CNStringstr1("abc ");
    CNString str2 = str1;

b)	字符串“+”运算

    CNStringstr1("abc"); 
    CNStringstr2("efg ");
    str1 = str1 + str2;    
   
c)	字符串“[]”运算

    CNString nstring1("abc");
    cout<< nstring1[0] ;// 则屏幕显示a
    cout<< nstring1[2] ; // 则屏幕显示c

d)	“<”运算符

    CNStringstr1("abc");
    CNStringstr2("efg");
    if (str1 <str2 ){
    cout<<“str1<str2”<<endl;
    }

e)	“>”运算符

    CNStringstr1("abc");
    CNStringstr2("efg");
    if (str1 >str2 ){
    cout<<“str1>str2”<<endl;
    }

f)	“==”运算符

    CNStringstr1("abc");
    CNStringstr2("efg");
    if (str1 == str2){
    cout<<“str1==str2”<<endl;
    }

#### 2.1.1.3. 题目3
创建双向链表类，该类有默认构造函数、类的拷贝函数、类的析构函数、实现链表添加数据、升序排序、查找链表中某个节点及删除链表中某个节点的操作（禁用STL及String类））。（25分）

#### 2.1.1.4. 题目4
设计并编写代码自动格斗类游戏。（25分）

1）	角色类CRole为基类

    构造函数、析构函数；
    成员变量：头像、HP（血量）、ATK（攻击力）、DEF（防御力）、Lv（等级），EXP（经验值）；
    成员函数：武器攻击、跳跃。

2）英雄类CHero继承于CRole类

    构造函数、析构函数；
    英雄类新增技能踢腿（成员函数）、抱摔（成员函数），给对方造成伤害具体值由学员自己进行设定；

3）敌人类CEnemy继承于CRole类

    构造函数、析构函数； 
    新增技能劈掌（成员函数）、连环腿（成员函数），给对方造成伤害值由学员自己进行设定；

4）战斗类CBattle

    构造函数、析构函数及其他成员函数
    双方HP(血量)初始值为100，开始战斗以后，英雄和敌人轮流攻击对方，掉血量=攻击方技能伤害值+ATK（攻击方的攻击力）-DEF（防御方的防御力），当一方血量为0时，战斗结束，玩家经验值增加相应点数，当经验等级达一定时候，玩家等级提升。

### 2.1.2. 任务提交
- 提交以上题目的工程代码(关键地方需注释说明)。
- 平台为VS2013(及以上版本) C++ win32控制台；
- 请按自己的思路进行设计和开发，不可抄袭其他人作品（包括网络上的），否则按作弊处理（0分）。


--------

# 3. U3D

这一部分任务属于U3D。

## 3.1. Csharp

![阶段一任务卡片图](https://wushuangabao.github.io/img/netdragon/u1.png)

### 3.1.1. 题目
用C# 实现一个小型连锁超市的库存管理，连锁超市在全国可能有多个仓库，可以查询指定仓库的商品库存情况，实现以下功能：

- 商品信息管理（增加、删除、修改、查询） 
- 货架信息管理（增加、删除、修改、查询）  
- 仓库信息管理（增加、删除、修改、查询）  
- 商品出库/入库管理	
- 查询库存数量前三名的商品              
- 统计指定仓库所有商品总价值       
- 退出系统                                   

#### 3.1.1.1. 内容要求

商品基本信息

    商品编号+ 名称+类型+单价+计量单位+数量

货架基本信息

	货架编号+总层数

仓库基本信息

    仓库编号+地址

商品出入库管理

    完成商品出入库功能，更新货架商品信息

查询仓库库存数量前三名商品

    可以按仓库、类型统计数量最多的前三名商品

数据存储

    录入及修改后的数据需保存到本地文件或数据库

以上提供基本的一些内容要求，学员们可以根据自身理解情况进行适当扩展。

#### 3.1.1.2. 技能要求
- 平台为VS2013或VS2015 , 控制台或Windows窗体应用程序；
- 充分使用派生类、基类和接口；
- 运用文件存储或数据库存储。
- 清晰的注释和良好的编码习惯；
- 视系统需要，采用一到两种设计模式。

#### 3.1.1.3. 设计文档要求
- 用UML类图画出系统中的类结构。
- 用UML时序图画出商品入库流程。

### 3.1.2. 诚信要求
- 请按自己的思路进行设计和开发，不可抄袭其他人作品，否则，按作弊处理。

### 3.1.3. 提交清单
- 设计文档：扩展策划说明、核心功能代码说明
- 项目目录：执行文件、工程文件及源码
- 第三方插件：如有第三方插件，请提供第三方插件包
- 资源文件：如果有使用其它资源文件(音效\模型\图片等)，请在项目目录中提供相关资源文件


