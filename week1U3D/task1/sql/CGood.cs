using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace task1
{
    class CGood : InterfaceSQL
    {
        string name;
        string type;
        float price;
        string unit;
        uint count;

        public CGood()
        {
            this.name = "";
            this.type = "";
            this.price = 0;
            this.unit = "";
            this.count = 0;
        }

        public CGood(string name, string type, float price, string unit, uint count)
        {
            this.name = name;
            this.type = type;
            this.price = price;
            this.unit = unit;
            this.count = count;
        }

        #region 接口实现

        public void recordDelete(MySqlConnection con)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// 向数据库的goods表中增加商品记录
        /// </summary>
        /// <param name="con"></param>
        public void recordInsert(MySqlConnection con)
        {
            MySqlCommand cmd = con.CreateCommand();
            cmd.CommandText = "INSERT INTO `goods` (`name`, `type`, `price`, `unit`, `count`) VALUES(@name, @type, @price, @unit, @count)";
            cmd.Parameters.AddWithValue("@name", name);
            cmd.Parameters.AddWithValue("@type", type);
            cmd.Parameters.AddWithValue("@price", price);
            cmd.Parameters.AddWithValue("@unit", unit);
            cmd.Parameters.AddWithValue("@count", count);
            try { cmd.ExecuteNonQuery(); }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 查询数据库中的商品表，刷新数据表
        /// </summary>
        /// <param name="con">数据库</param>
        /// <param name="dataGridView">数据表</param>
        public void recordSelect(MySqlConnection con, DataGridView dataGridView)
        {
            // 用MySqlDataAdapter的方法填充数据表
            try
            {
                DataSet ds = new DataSet();
                MySqlDataAdapter adapter = new MySqlDataAdapter("SELECT* FROM `goods`", con);
                MySqlCommandBuilder cb = new MySqlCommandBuilder(adapter);
                adapter.Fill(ds, "Goods");
                dataGridView.DataSource = ds;
                dataGridView.DataMember = "Goods";
                ((FormGood)dataGridView.Parent).setAdapter(adapter);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public void recordUpdate(MySqlConnection con)
        {
            throw new NotImplementedException();
        }
        #endregion
    }
}
