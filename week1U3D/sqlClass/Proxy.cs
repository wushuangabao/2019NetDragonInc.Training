using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace task1
{
    /// <summary>
    /// 代理者类，负责封装对数据库的操作
    /// </summary>
    class Proxy : InterfaceSQL
    {
        InterfaceSQL realSubject = null;
        string strConnection = "Server=localhost;Database=market;Uid=root;Charset=utf8";
        MySqlConnection connection = null;

        public DataGridView dataGridView = null;
        public bool successed = false;


        /// <summary>
        /// 构造代理者
        /// </summary>
        /// <param name="realSub">被代理的实体（被代理的是商品、仓库还是货架）</param>
        /// <param name="dataGridView">数据表控件</param>
        public Proxy(InterfaceSQL realSub, DataGridView dataGridView)
        {
            realSubject = realSub;
            this.dataGridView = dataGridView;
        }

        /// <summary>
        /// 指定被代理者
        /// </summary>
        /// <param name="realSub">被代理的实体</param>
        internal void setRealSubject(InterfaceSQL realSub)
        {
            realSubject = realSub;
        }

        /// <summary>
        /// 预处理
        /// </summary>
        private void before()
        {
            if (connection == null)
                connection = new MySqlConnection(strConnection);
            try { connection.Open(); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        /// <summary>
        /// 善后处理
        /// </summary>
        private void after()
        {
            connection.Close();
        }

        #region 接口的实现

        public void recordDelete(MySqlConnection con)
        {
            before();
            realSubject.recordDelete(connection);
            after();
        }

        /// <summary>
        /// 增添记录
        /// </summary>
        /// <param name="con">无意义</param>
        public void recordInsert(MySqlConnection con)
        {
            before();
            realSubject.recordInsert(connection);
            after();
        }

        /// <summary>
        /// 查询记录
        /// </summary>
        /// <param name="con">无意义</param>
        /// <param name="dataGridView">数据表控件，用来存放查询结果</param>
        public void recordSelect(MySqlConnection con, DataGridView dataGridView)
        {
            before();
            realSubject.recordSelect(connection, dataGridView);
            after();
        }

        public void recordUpdate(MySqlConnection con)
        {
            before();
            realSubject.recordUpdate(connection);
            after();
        }
        #endregion
    }
}
