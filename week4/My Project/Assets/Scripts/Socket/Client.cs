using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class Client : MonoBehaviour
{
    static Client _instance;
    static public Client Instance { get { return _instance; } }

    // 服务器IP地址、端口号
    IPAddress ip = IPAddress.Parse("127.0.0.1");
    int port = 4000;

    Socket socket;
    string username = "";
    string msg = "";
    Thread thread;

    // 存储接受到的消息
    byte[] buffer = new byte[1024];

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
    }

    void Start()
    {
        StartClient();
    }

    void Update()
    {
        // 消息显示（只能在主线程中操作游戏对象）
        if(username!="" && msg != "")
        {
            ChatPanel.Instance.ShowInfo(username,msg);
            username = "";
            msg = "";
        }
    }

    /// <summary>
    /// 建立客户端，连接到服务器
    /// </summary>
    public void StartClient()
    {
        IPEndPoint ipp = new IPEndPoint(ip,port);
        socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        Debug.Log("建立客户端...");
        try
        {
            // 向服务器发起Socket连接
            socket.Connect(ipp);
            // 开启线程，接收服务器回传的消息
            thread = new Thread(new ThreadStart(ReceiveInfo));
            // 将线程设置为后台线程（会随主线程的关闭而关闭）
            thread.IsBackground = true;
            // 开启线程
            thread.Start();
        }
        catch (Exception e)
        {
            Debug.Log(e.ToString());
        }
    }

    /// <summary>
    /// 发送消息
    /// </summary>
    public void SendInfo(string m)
    {
        Debug.Log("发送消息：" + m);
        socket.Send(Encoding.ASCII.GetBytes(m));
    }

    /// <summary>
    /// 接收消息
    /// </summary>
    public void ReceiveInfo()
    {
        while (true)
        {
            try
            {
                // 检查socket的当前连接状态
                if (!socket.Connected)
                {
                    Dispose();
                    break;
                }
                // 接收消息
                int length = socket.Receive(buffer);
                if(length > 0)
                {
                    // 解析消息
                    string data = Encoding.ASCII.GetString(buffer, 0, length);
                    //string[] strList = data.Split('#');
                    //username = strList[0];
                    //msg = strList[1];
                }
            }
            catch (Exception e)
            {
                Debug.Log(e.ToString());
                Dispose();
                break;
            }
            Thread.Sleep(100);
        }
    }

    // 脚本的生命周期结束
    void OnDestroy()
    {
        Dispose(); //unity中须要显式的清理
    }

    /// <summary>
    /// 清理连接和线程
    /// </summary>
    void Dispose()
    {
        // 终止线程
        if (thread != null)
        {
            if (thread.ThreadState != ThreadState.Aborted)
            {
                thread.Abort();
            }
            thread = null;
        }
        // 关闭连接
        if (socket!=null && socket.Connected)
        {
            socket.Shutdown(SocketShutdown.Both); //禁用收发消息
            socket.Close();
            Debug.Log("与服务器断开了连接！");
        }
    }
}
