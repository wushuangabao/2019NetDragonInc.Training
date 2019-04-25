## week3工程说明

名为week3的工程是我18年创建的，它使用MySQL API的方式调用数据库，数据库创建文件是gamedb.sql。

详细资料见我的C++学习笔记：

- [第三阶段任务（数据库）](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BB%BB%E5%8A%A1%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89.html)
- [第三阶段作业（数据库）环境设置](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89%E7%8E%AF%E5%A2%83%E8%AE%BE%E7%BD%AE.html)
- [第三阶段作业（数据库）操作演示](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89%E6%93%8D%E4%BD%9C%E6%BC%94%E7%A4%BA.html)

## myproject说明

这个工程是我19年（现在）创建的，原本打算使用[MySQL Connector](https://dev.mysql.com/downloads/connector/cpp/)的方式调用数据库，不过看了下今年的要求只说了使用MySQL API，只好作罢。

今年打算实现数据库连接池。下面介绍开发环境的配置：

（操作系统是win7，Visual Studio版本是2017。）

### 1. 安装MySQL

[官网](https://www.mysql.com/downloads/)下载，我选择的版本是MySQL Community Server 5.7.25 64位。

### 2. 创建服务器环境

我将XAMPP中的MySQL版本换成了我刚才安装的5.7.25版（遇到各种错误，全靠百度解决了，其中[这篇](https://blog.csdn.net/mhmyqn/article/details/17043921)挺有用的）。

后来我发现更换XAMPP自带的MySQL后，在MySQL数据库备份SQL文件时会遇到一系列问题导致无法备份。故我又卸载XAMPP、移除MySQL服务，重新**开启MySQL服务**（中间遇到无法开启的问题，原因是没有先在mysql的bin目录下执行mysqld  --initialize-insecure进行初始化）。

### 3. 创建数据库

使用可视化的数据库管理工具Navicat for MySQL来方便地创建数据库。新建一个连接，名为test，**主机名localhost（IP为127.0.0.1），用户名root，密码为空字符串**。

新建一个数据库，名为**chat**，字符集utf8 -- UTF-8 Unicode，排序规则utf8_ general_ci。打开刚创建的chat数据库，新建3张表：**用户表user、角色表role、聊天消息表record**。注意：

- 最好每张表都设置一个int类型的id字段，勾选无符号、自动递增、不能为null，作为表的主键。
- 知道char, varchar, text的[区别](https://www.cnblogs.com/Lance--blog/p/5193027.html)，合理运用这些数据类型。
- 为经常需要搜索的字段建立索引，可以提高搜索效率。
- 设置索引类型为Unique，可以使非主键字段也不可重复。
- 我的[笔记](https://wushuangabao.github.io/CSharp/UseMySql)中记录了如何正确使用外键。

建好chat数据库后，备份为chat.sql文件。

### 4. 创建C++控制台项目

创建新的C++ Console工程后，首先进行**项目属性的配置：**

- 如果库是x64类型的，项目的**平台**也要改为**x64**。
- **附加包含目录：**将官网下载的MySQL目录下include文件夹的完整路径添加到C/C++的附加包含目录表中。
- **附加库目录：**将官网下载的MySQL目录下lib文件夹的完整路径添加到链接器的附加库目录表中。
- **添加动态库：**这里需要添加mysql的库文件，因为上一步我们已经添加了库所在的目录，因此在这里可以直接添加现有的库即可。链接器-输入，在附加依赖项中写入**libmysql.lib**。
- 若winsows系统中缺少libmysql，将MySQL目录下lib文件夹中的**libmysql.dll**文件复制到系统目录（Windows/system）下

----

经过以上配置，C++程序已经可以连接到数据库，后面就开始敲代码了。



