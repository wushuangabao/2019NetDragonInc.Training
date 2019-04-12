using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace WindowsFormsClient
{
    public partial class FClient : Form
    {
        private int length;
        object objLock = new object();
        byte[] userName;
        Socket socketClient = null;
        Thread threadClient = null;

        public FClient()
        {
            InitializeComponent();
            //关闭对文本框的非法线程操作检查
            TextBox.CheckForIllegalCrossThreadCalls = false;
            this.ControlBox = false;
            userName = Encoding.UTF8.GetBytes("user" + GetCurrentTime().Minute * GetCurrentTime().Second);
            btnSend.Enabled = false;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                e.Handled = true;   //将Handled设置为true，指示已经处理过KeyPress事件  
                button1_Click(sender, e);
            }
        }

        //发送按钮
        private void button1_Click(object sender, EventArgs e)
        {
            byte[] arrClientSendMsg = Encoding.UTF8.GetBytes(txtCMsg.Text.Trim());
            commum.Message msg = new commum.Message();
            msg.message = arrClientSendMsg;
            msg.ipAddress = userName;
            arrClientSendMsg = PackCodec.Serialize<commum.Message>(msg);
            SendMsg(arrClientSendMsg);
        }

        //连接按钮点击事件
        private void btnBeginListen_Click(object sender, EventArgs e)
        {
            socketClient = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress ipaddress = IPAddress.Parse(txtIP.Text.Trim());
            IPEndPoint endpoint = new IPEndPoint(ipaddress, int.Parse(txtPort.Text.Trim()));
            try
            {
                socketClient.Connect(endpoint);
            }
            catch (Exception)
            {
                txtMsg.AppendText("连接失败\r\n");
                return;
            }

            txtMsg.AppendText("连接成功\r\n");
            threadClient = new Thread(RecMsg);
            threadClient.IsBackground = true;
            threadClient.Start();
            btnBeginListen.Enabled = false;
        }

        private void btnSend_Load(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// protobuf包发送方法
        /// </summary>
        public void SendMsg(byte[] arrClientSendMsg)
        {
            try
            {
                socketClient.Send(arrClientSendMsg);
            }
            catch (SocketException)
            {
                txtMsg.AppendText("请连接后再尝试\r\n");
                return;
            }
            catch (NullReferenceException)
            {
                txtMsg.AppendText("请连接后再尝试\r\n");
                return;
            }
        }

        /// <summary>
        /// 接收服务端发来信息的方法
        /// </summary>
        private void RecMsg()
        {
            byte[] arrRecMsg = new byte[1024];
            while (true) //持续监听服务端发来的消息
            {
                commum.Message msg = new commum.Message();
                //将客户端套接字接收到的数据存入内存缓冲区, 并获取其长度
                try
                {
                    Array.Clear(arrRecMsg, 0, 1024);
                    socketClient.Receive(arrRecMsg);
                }
                catch (SocketException)
                {
                    string str = "网络错误，请退出聊天室";
                    txtMsg.AppendText("我:" + GetCurrentTime() + "\r\n" + str + "\r\n");
                    return;
                }
                lock (objLock)
                {
                    //获取传输的数据中数据的位数
                    for (length = 0; arrRecMsg[length] != '\0' || length > 1024; length++)
                    {

                    }
                    //越界
                    if (length > 1024)
                        continue;
                    byte[] rec = new byte[length];
                    Array.Clear(rec, 0, length);
                    for (int i = 0; i < length; i++)
                    {
                        rec[i] = arrRecMsg[i];
                    }
                    msg = PackCodec.Deserialize<commum.Message>(rec);
                    if (msg == null)
                        continue;
                    string strRecMsg = Encoding.UTF8.GetString(msg.message, 0, msg.message.Length);
                    string strRecName = Encoding.UTF8.GetString(msg.ipAddress, 0, msg.ipAddress.Length);
                    if (strRecName.Equals("0"))//其他信息
                    {
                        txtMsg.AppendText(strRecMsg + "\r\n");
                    }
                    else
                    {
                        txtMsg.AppendText(strRecName + ":" + GetCurrentTime() + "\r\n" + strRecMsg + "\r\n");
                    }
                }
            }
        }

        private void txtMsg_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void txtMsg_TextChanged(object sender, EventArgs e)
        {

        }

        private void txtCMsg_TextChanged(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// 获取当前系统时间的方法
        /// </summary>
        /// <returns>当前时间</returns>
        private DateTime GetCurrentTime()
        {
            DateTime currentTime = new DateTime();
            currentTime = DateTime.Now;
            return currentTime;
        }

        //退出按钮点击事件
        private void buttonClose_Click(object sender, EventArgs e)
        {
            //如果还未建立连接
            if (socketClient == null)
            {
                this.Close();
                return;
            }
            //如果已经建立连接
            try
            {
                byte[] arrClientSendMsg = Encoding.UTF8.GetBytes(Encoding.UTF8.GetString(userName, 0, userName.Length) + "退出了聊天室");
                commum.Message msg = new commum.Message();
                msg.message = arrClientSendMsg;
                msg.ipAddress = userName;
                arrClientSendMsg = PackCodec.Serialize<commum.Message>(msg);
                SendMsg(arrClientSendMsg);

                socketClient.Shutdown(SocketShutdown.Both);
                this.Close();
            }
            catch (SocketException)
            {
                txtMsg.AppendText("当前未连接\r\n");
                this.Close();
                return;
            }
            catch (NullReferenceException)
            {
                return;
            }
        }

        private void buttonLogin_Click(object sender, EventArgs e)
        {
            byte[] arrClientSendMsg = Encoding.UTF8.GetBytes(Encoding.UTF8.GetString(userName, 0, userName.Length) + "进入了聊天室");
            commum.Message msg = new commum.Message();
            msg.message = arrClientSendMsg;
            msg.ipAddress = userName;
            arrClientSendMsg = PackCodec.Serialize<commum.Message>(msg);
            SendMsg(arrClientSendMsg);

            btnSend.Enabled = true;
            buttonLogin.Enabled = false;
        }
    }
}
