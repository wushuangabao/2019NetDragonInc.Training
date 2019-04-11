using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace task1
{
    class CGoodsStore : InterfaceSQL
    {
        /// <summary>
        /// 成员变量
        /// </summary>
        uint goods;
        uint warehouse;
        uint shelf;
        uint shelf_storey;
        long count;

        /// <summary>
        /// 构造：出入库操作的对象
        /// </summary>
        /// <param name="g">商品id</param>
        /// <param name="w">仓库id</param>
        /// <param name="s">货架id</param>
        /// <param name="ss">货架第几层</param>
        /// <param name="c">商品增加数量（负数表示减少）</param>
        public CGoodsStore(uint g, uint w, uint s, uint ss, long c)
        {
            goods = g;
            warehouse = w;
            shelf = s;
            shelf_storey = ss;
            count = c;
        }

        public void recordDelete(MySqlConnection con)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// 向数据库的出入库表中添加数据
        /// </summary>
        /// <param name="con">数据库连接</param>
        public void recordInsert(MySqlConnection con)
        {
            // 保存商品的数量
            long goods_count = 0;
            MySqlCommand cmd1 = con.CreateCommand();
            cmd1.CommandText = "SELECT * FROM `goods` WHERE `id` = '" + goods + "'";
            try
            {
                MySqlDataReader rdr = cmd1.ExecuteReader();
                if (rdr.Read())
                    goods_count = Convert.ToInt64(rdr["count"]);
                rdr.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            // 查询商品ID、仓库ID、货架ID是否存在，货架第shelf_storey层是否能放下count数目的该商品(TODO)
            if (false)
            {
                MessageBox.Show("商品出入库的数据不合法，请检查");
                return;
            }

            // 改变商品的数量
            goods_count += count;
            if (goods_count < 0)
            {
                MessageBox.Show("无法提供足够数量的商品");
                return;
            }

            // 添加“出入库”记录
            cmd1.CommandText = "INSERT INTO `goods_store` (`goods`, `warehouse`, `shelf`, `shelf_storey`, `count`) VALUES(@g, @w, @s, @ss, @c)";
            cmd1.Parameters.AddWithValue("@g", goods);
            cmd1.Parameters.AddWithValue("@w", warehouse);
            cmd1.Parameters.AddWithValue("@s", shelf);
            cmd1.Parameters.AddWithValue("@ss", shelf_storey);
            cmd1.Parameters.AddWithValue("@c", count);

            // 更新商品的数量
            MySqlCommand cmd2 = con.CreateCommand();
            cmd2.CommandText = "UPDATE `goods` SET `count`=@gc WHERE (`id`=@g)";
            cmd2.Parameters.AddWithValue("@g", goods);
            cmd2.Parameters.AddWithValue("@gc", goods_count);

            // 执行sql
            try
            {
                cmd1.ExecuteNonQuery();
                cmd2.ExecuteNonQuery();
                MessageBox.Show("操作成功！");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        public void recordSelect(MySqlConnection con, DataGridView dataGridView)
        {
            throw new NotImplementedException();
        }

        public void recordUpdate(MySqlConnection con)
        {
            throw new NotImplementedException();
        }
    }
}
