## week3文件说明

名为week3的文件夹中的源码是我18年写的，它使用MySQL API的方式调用数据库，数据库创建文件是gamedb.sql。

详细资料见我的C++学习笔记：

- [第三阶段任务（数据库）](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BB%BB%E5%8A%A1%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89.html)
- [第三阶段作业（数据库）环境设置](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89%E7%8E%AF%E5%A2%83%E8%AE%BE%E7%BD%AE.html)
- [第三阶段作业（数据库）操作演示](https://wushuangabao.github.io/Cpp/%E7%AC%AC%E4%B8%89%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%EF%BC%88%E6%95%B0%E6%8D%AE%E5%BA%93%EF%BC%89%E6%93%8D%E4%BD%9C%E6%BC%94%E7%A4%BA.html)

## myproject说明

这个工程是我19年（现在）创建的，原本打算使用[MySQL Connector](https://dev.mysql.com/downloads/connector/cpp/)的方式调用数据库，不过看了下今年的要求只说了使用MySQL API，只好作罢。

今年打算实现数据库连接池。开发环境：操作系统win7，Visual Studio版本2017。

## 优秀作业说明

网龙的老师从同学们提交的作业中选出来的。

其中，张镇在第二阶段C/S端的基础上实现了数据库操作；郑仁法做的其实和我的差不多。

**周老师：**

下面我们来看一下第三阶段作业中存在的一些问题：

1.	用户输入和数据库操作逻辑混合在一起。
2.	菜单操作与业务逻辑处理最好分开到不同的文件中。
3.	所有功能都写在一个main函数中，缺少面向对象封装思想，还是C语言的面向过程的思维，没有将相关方法独立成类方法。
4.	业务逻辑和数据库操作混杂在一起，二者最好要分开，比如业务层的逻辑是添加用户，应该将添加user表记录以及添加用户角色关系表记录这两个数据库操作分别抽取到数据层对应的UserDao类以及RoleDao类中，这样利于数据库操作的复用，比如有多个地方都要用到根据用户ID查询用户，就可以调用同一个函数，减少代码冗余。
5.	事务：事务的使用比较生硬，只有一条sql语句的，不需要使用事务，事务是在有多个sql语句（尤其是更新）的时候才需要使用。
6.	使用MySQL的C库的同学，有的没有实现事务操作功能，同样可以实现事务功能，可以使用`mysql_autocommit(&mysql, 0);`关闭自动提交，操作失败使用`mysql_rollback()`回滚，操作成功以后，可以使用`mysql_commit()`手动提交，`mysql_autocommit(&mysql, 1);`开启自动提交。此外，有的同学通过直接发送sql语句实现事务，比如`this->sql("set autocommit=0;");`、`this->sql("rollback;");`，这种方式不够好,存在拼写错误的可能。
7.	内存泄漏：使用malloc方法申请内存，后面没有调用free释放内存。
8.	不同业务对应的不同表的操作最好也要分开，不要混在一起。
9.	代码规范：类名和方法名不够规范，建议可以命名为UpdateUserName、DeleteUserById等等。