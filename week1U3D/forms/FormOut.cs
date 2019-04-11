using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace task1.forms
{
    public partial class FormOut : Form
    {
        /// <summary>
        /// 出入库操作的相关信息
        /// </summary>
        uint goods = 1;
        uint warehouse = 1;
        uint shelf = 1;
        uint shelf_storey = 2;
        uint count = 1;

        public FormOut()
        {
            InitializeComponent();
        }

        #region 表单处理

        /// <summary>
        /// 输入商品ID
        /// </summary>
        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            try { goods = Convert.ToUInt16(textBox6.Text); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        /// <summary>
        /// 输入仓库ID
        /// </summary>
        private void textBox7_TextChanged(object sender, EventArgs e)
        {
            try { warehouse = Convert.ToUInt16(textBox7.Text); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        /// <summary>
        /// 输入货架ID
        /// </summary>
        private void textBox8_TextChanged(object sender, EventArgs e)
        {
            try { shelf = Convert.ToUInt16(textBox8.Text); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        /// <summary>
        /// 输入：货架的第几层
        /// </summary>
        private void textBox9_TextChanged(object sender, EventArgs e)
        {
            try { shelf_storey = Convert.ToUInt16(textBox9.Text); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        /// <summary>
        /// 输入：出入库商品的数量
        /// </summary>
        private void textBox10_TextChanged(object sender, EventArgs e)
        {
            try { count = Convert.ToUInt16(textBox10.Text); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        #endregion

        /// <summary>
        /// 出库
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            Proxy proxy = new Proxy(new CGoodsStore(goods,warehouse,shelf,shelf_storey,-count), null);
            proxy.recordInsert(null);
        }

        /// <summary>
        /// 入库
        /// </summary>
        private void button2_Click(object sender, EventArgs e)
        {
            Proxy proxy = new Proxy(new CGoodsStore(goods, warehouse, shelf, shelf_storey, count), null);
            proxy.recordInsert(null);
        }
    }
}
