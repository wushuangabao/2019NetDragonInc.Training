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
    /// 封装增删改查操作的接口
    /// </summary>
    interface InterfaceSQL
    {
        void recordInsert(MySqlConnection con);
        void recordDelete(MySqlConnection con);
        void recordUpdate(MySqlConnection con);
        void recordSelect(MySqlConnection con, DataGridView dataGridView);
    }
}
