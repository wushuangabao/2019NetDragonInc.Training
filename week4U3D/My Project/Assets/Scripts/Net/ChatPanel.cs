using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using MiniJSON;

public class ChatPanel : MonoBehaviour
{
    static ChatPanel _instance;
    static public ChatPanel Instance { get { return _instance; } }

    // 输入框、文本
    public InputField iFMessage;
    public Text textChat;

    string userName = "testUser";
    string msg = "";

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        textChat.text = "";
        iFMessage.text = "";
        iFMessage.ActivateInputField();
    }

    void Start()
    {
        iFMessage.onValueChanged.AddListener(delegate
        {
            // 将输入值保存到msg
            msg = iFMessage.text;
        });
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.KeypadEnter))
        {
            iFMessage.ActivateInputField();
            //EventSystem.current.SetSelectedGameObject(iFMessage.gameObject);
            if (msg != "")
            {
                // 发消息给服务器
                SendInfo();
                // 清空消息输入框
                iFMessage.text = "";
                // 恢复对角色的控制
                UserControl.currentControl = true;
            }
            else
            {
                // 取消/恢复对角色的控制
                UserControl.currentControl = !UserControl.currentControl;
            }
        }
    }

    /// <summary>
    /// 显示消息到textChat
    /// </summary>
    public void ShowInfo(string username,string msg)
    {
        if (textChat.text != "")
            textChat.text += "\n";
        // 用户名显示为红色
        textChat.text += "<color=red>" + username + "</color> " + msg;
    }

    /// <summary>
    /// 发送消息到服务器
    /// </summary>
    public void SendInfo()
    {
        var dict = new Dictionary<string, object>
        {
            ["instruct"] = false,
            ["name"] = userName,
            ["time"] = "today",
            ["str"] = msg
        };
        Client.Instance.SendInfo(dict);
    }

    /// <summary>
    /// 获取用户名
    /// </summary>
    public string GetUserName()
    {
        return userName;
    }
}
