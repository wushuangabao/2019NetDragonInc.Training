using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace task1.forms
{
    public partial class FormGood : Form
    {
        /// <summary>
        /// 商品信息
        /// </summary>
        string name = "肥皂";
        string type = "生活用品";
        float price = 5F;
        string unit = "块";
        uint count = 0;

        /// <summary>
        /// 成员变量
        /// </summary>
        MySqlDataAdapter adapter = null;
        Proxy proxy = null;

        /// <summary>
        /// 构造函数
        /// </summary>
        public FormGood()
        {
            InitializeComponent();

            // 初始化代理者（代理商品类），并查询整个商品表
            proxy = new Proxy(new CGood(),dataGridView);
            proxy.recordSelect(null,dataGridView);
        }

        /// <summary>
        /// 设置adapter
        /// </summary>
        internal void setAdapter(MySqlDataAdapter adp)
        {
            adapter = adp;
        }

        /// <summary>
        /// 向商品表中增添记录
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            // 检查商品信息是否合法(TODO)
            if (false)
            {
                MessageBox.Show("商品信息填写不规范！");
                return;
            }
            // 实例化商品类，并委托给代理者类添加到数据库
            CGood good = new CGood(name, type, price, unit, count);
            proxy.setRealSubject(good);
            proxy.recordInsert(null);
        }

        /// <summary>
        /// 修改商品表，提交给数据库并刷新商品表
        /// </summary>
        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                adapter.Update((DataSet)dataGridView.DataSource, "goods");
                proxy.recordSelect(null, dataGridView);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        #region 表单处理
        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            try { this.price = Convert.ToSingle(textBox3.Text); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            try { this.type = textBox2.Text; }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            try { this.name = textBox1.Text; }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            try { this.unit = textBox4.Text; }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        #endregion

    }
}
