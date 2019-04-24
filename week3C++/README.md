## week3工程说明

名为week3的工程是我18年创建的，它使用MySQL API的方式调用数据库，数据库创建文件是gamedb.qsl。

详细资料见我的C++学习笔记：

- [第三阶段任务（数据库）](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BB%BB%E5%8A%A1%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89.html)
- [第三阶段作业（数据库）环境设置](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89%E7%8E%AF%E5%A2%83%E8%AE%BE%E7%BD%AE.html)
- [第三阶段作业（数据库）操作演示](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89%E6%93%8D%E4%BD%9C%E6%BC%94%E7%A4%BA.html)

## myproject说明

这个工程是我19年（现在）创建的，原本打算使用[MySQL Connector](https://dev.mysql.com/downloads/connector/cpp/)的方式调用数据库，不过看了下今年的要求只说了使用MySQL API，只好作罢。

今年打算使用Qt做图形化的数据库操作界面，并且实现数据库连接池。

### 1. 安装MySQL

[官网](https://www.mysql.com/downloads/)下载，我选择的版本是MySQL Community Server 5.7.25 64位

### 2. 创建服务器环境

我在U3D阶段一任务中已经下载了XAMPP，详见[笔记](https://wushuangabao.github.io/CSharp/UseMySql)

现在我要将XAMPP中的MySQL版本换成我刚才安装的那个——参考[更换步骤](https://jingyan.baidu.com/article/7f41ecec38d60b593c095c4a.html)（按照这个步骤安装还会遇到各种错误，全靠百度解决了，其中[这篇](https://blog.csdn.net/mhmyqn/article/details/17043921)挺有用的）

### 3. 创建数据库

使用可视化的数据库管理工具Navicat for MySQL来方便地创建数据库。新建的数据库名为testdb，主机名localhost（IP为127.0.0.1），用户名root，密码为空字符串。

建立3张表：用户表、角色表、聊天消息表。

