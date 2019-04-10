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

namespace task1
{
    public partial class Form1 : Form
    {
        private Proxy proxy = null;
        private MySqlDataAdapter adapter = null;
        private string strTable = "";

        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 设置adapter
        /// </summary>
        internal void setAdapter(MySqlDataAdapter adp)
        {
            adapter = adp;
        }

        /// <summary>
        /// 货架管理(增删改查)
        /// </summary>
        private void button5_Click(object sender, EventArgs e)
        {
            try
            {
                proxy = new Proxy(new CShelf(), dataGridView);
                proxy.recordSelect(null, dataGridView);
                strTable = "shelves";
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 商品信息管理(增删改查)
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                FormGood formGood = new FormGood();
                formGood.Show(this);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 仓库信息管理(增删改查)
        /// </summary>
        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                proxy = new Proxy(new CWareHouse(), dataGridView);
                proxy.recordSelect(null, dataGridView);
                strTable = "warehouse";
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 确认对数据表的修改，提交给数据库
        /// </summary>
        private void button6_Click(object sender, EventArgs e)
        {
            try
            {
                if (strTable == "warehouse")
                {
                    adapter.Update((DataSet)dataGridView.DataSource, strTable);
                    proxy.setRealSubject(new CWareHouse());
                    proxy.recordSelect(null, dataGridView);
                }
                else if (strTable == "shelves")
                {
                    adapter.Update((DataSet)dataGridView.DataSource, strTable);
                    proxy.setRealSubject(new CShelf());
                    proxy.recordSelect(null, dataGridView);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 商品入库
        /// </summary>
        private void button2_Click(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// 商品出库
        /// </summary>
        private void button3_Click(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// 查询指定条件的商品的库存量
        /// </summary>
        private void button7_Click(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// 查询指定仓库的商品总价值量
        /// </summary>
        private void button8_Click(object sender, EventArgs e)
        {

        }
    }
}
