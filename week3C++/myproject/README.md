
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

* [开发环境配置](#开发环境配置)
	* [1. 安装MySQL](#1-安装mysql)
	* [2. 开启MySQL服务](#2-开启mysql服务)
	* [3. 创建数据库](#3-创建数据库)
	* [4. 配置C++控制台项目](#4-配置c控制台项目)
* [设计C++类](#设计c类)
	* [1. DB](#1-db)
	* [2. ConnPool](#2-connpool)
	* [3. CSql](#3-csql)

<!-- /code_chunk_output -->


# 开发环境配置

操作系统是win7，Visual Studio版本是2017

## 1. 安装MySQL

[官网](https://www.mysql.com/downloads/)下载，我选择的版本是MySQL Community Server 5.7.25 64位。

## 2. 开启MySQL服务

参考[帖子](https://blog.csdn.net/mhmyqn/article/details/17043921)开启MySQL服务（中间遇到无法开启的问题，原因是没有先在mysql的bin目录下执行mysqld  --initialize-insecure进行初始化）。

## 3. 创建数据库

使用可视化的数据库管理工具Navicat for MySQL来方便地创建数据库。新建一个连接，名为test，**主机名localhost（IP为127.0.0.1），用户名root，密码为空字符串**。

新建一个数据库，名为**chat**，字符集utf8 -- UTF-8 Unicode，排序规则utf8_ general_ci。打开刚创建的chat数据库，新建3张表：**用户表user、角色表role、聊天消息表record**。

建好chat数据库后，备份为chat.sql文件。

## 4. 配置C++控制台项目

创建新的C++ Console工程后，首先进行**项目属性的配置：**

- 如果库是x64类型的，项目的**平台**也要改为x64。
- **附加包含目录**：将官网下载的MySQL目录下include文件夹的完整路径添加到C/C++的附加包含目录表中。
- **附加库目录**：将官网下载的MySQL目录下lib文件夹的完整路径添加到链接器的附加库目录表中。
- **添加动态库**：这里需要添加mysql的库文件，因为上一步我们已经添加了库所在的目录，因此在这里可以直接添加现有的库即可。链接器-输入，在附加依赖项中写入**libmysql.lib**。
- 若提示winsows系统中缺少libmysql.dll，将MySQL目录下lib文件夹中的libmysql.dll文件复制到系统目录（Windows/system）下。

# 设计C++类

简要说明我编写的DB类、CoonPool类和CSql类的功能。

## 1. DB

- 存储数据库的信息，IP地址、端口号、管理员账户和密码。
- 单例模式，本身只能存在一个实例。
- 带有一个数据库连接池。
- 拥有和处理各种逻辑相关的函数，如创建账户等。

## 2. ConnPool

- 数据库连接池类，提供一定数量的数据库连接。
- 程序可以取出连接，用完可以放回。
- 连接数据库、取出和放回时使用C++新特性lock_guard给线程加锁。

## 3. CSql

- 存储一个与数据库的连接。
- 封装了一些常用的SQL操作。
