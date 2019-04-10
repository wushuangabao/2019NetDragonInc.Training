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
    class CShelf: InterfaceSQL
    {
        public void recordDelete(MySqlConnection con)
        {
            throw new NotImplementedException();
        }

        public void recordInsert(MySqlConnection con)
        {
            throw new NotImplementedException();
        }

        public void recordSelect(MySqlConnection con, DataGridView dataGridView)
        {
            // 用MySqlDataAdapter的方法填充数据表
            try
            {
                DataSet ds = new DataSet();
                MySqlDataAdapter adapter = new MySqlDataAdapter("SELECT* FROM `shelves`", con);
                MySqlCommandBuilder cb = new MySqlCommandBuilder(adapter);
                adapter.Fill(ds, "Shelves");
                dataGridView.DataSource = ds;
                dataGridView.DataMember = "Shelves";
                ((Form1)dataGridView.Parent).setAdapter(adapter);
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
    }
}
