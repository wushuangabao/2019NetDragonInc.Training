using UnityEngine;
using UnityEngine.UI;

public class ChatPanel : MonoBehaviour
{
    static ChatPanel _instance;
    static public ChatPanel Instance { get { return _instance; } }

    // 面板、输入框、文本
    //public GameObject panelName;
    //public GameObject panelChat;
    public InputField iFName;
    public InputField iFMessage;
    public Text textChat;

    string userName = "";
    string msg = "";

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        textChat.text = "";
        iFName.text = "";
        iFMessage.text = "";
    }

    void Start()
    {
        ShowNamePanel();
    }

    void Update()
    {
        
    }

    /// <summary>
    /// 用户名输入结束，按回车若文本不空则进入聊天面板
    /// </summary>
    public void OnIFNameEndEdit()
    {
        // case:按下回车键
        if(Input.GetKeyDown(KeyCode.Return)|| Input.GetKeyDown(KeyCode.KeypadEnter))
        {
            if (iFName.text == "")
            {
                // 输入焦点指向用户名输入框
                iFName.ActivateInputField();
                return;
            }
            userName = iFName.text;
            HideNamePanel();
            ShowChatPanel();
        }
    }

    /// <summary>
    /// 消息输入结束，显示和发送消息
    /// </summary>
    public void OnIFMsgEndEdit()
    {
        if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.KeypadEnter))
        {
            iFMessage.ActivateInputField();
            if (msg == "")
                return;
            // 聊天面板显示消息
            ShowInfo(userName, msg);
            // 发消息给服务器
            SendInfo();
            // 清空消息输入框
            iFMessage.text = "";
        }
    }

    /// <summary>
    /// 消息输入，将输入值保存到msg
    /// </summary>
    public void OnIFMsgValueChange(string text)
    {
        msg = text;
    }

    /// <summary>
    /// 显示消息到textChat
    /// </summary>
    public void ShowInfo(string username,string message)
    {
        if (textChat.text != "")
            textChat.text += "\n";
        // 用户名显示为红色
        textChat.text += "<color=red>" + username + "</color>:" + msg;
    }

    /// <summary>
    /// 发送消息到服务器
    /// </summary>
    public void SendInfo()
    {
        Client.Instance.SendInfo(userName + "#" + msg);
    }

    void ShowNamePanel()
    {
        //panelName.SetActive(true);
        iFName.ActivateInputField();
    }

    void HideNamePanel()
    {
        //panelName.SetActive(false);
    }

    void ShowChatPanel()
    {
        //panelChat.SetActive(true);
        iFMessage.ActivateInputField();
    }
}
