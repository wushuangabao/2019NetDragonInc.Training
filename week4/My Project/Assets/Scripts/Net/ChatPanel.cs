using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

public class ChatPanel : MonoBehaviour
{
    static ChatPanel _instance;
    static public ChatPanel Instance { get { return _instance; } }

    public InputField iFMessage;
    public Text textChat;

    CanvasGroup canvasGroup;
    string userName = "testUser";
    string msg = "";
    bool isMenu = true; //是否处于菜单场景

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        textChat.text = "";
        iFMessage.text = "";
    }

    void Start()
    {
        // 监听输入值，将其保存到msg
        iFMessage.onValueChanged.AddListener(delegate
        {
            msg = iFMessage.text;
        });

        canvasGroup = GetComponentInChildren<CanvasGroup>();
        if (SceneManager.GetActiveScene().name=="Menu")
        {
            Hide(0.0f);
            GetComponentInChildren<Image>().color = Color.white;
            isMenu = true;
            SetUserName(Client.Instance.GetUserName());
        }
        else
        {
            Hide(0.2f);
            GetComponentInChildren<Image>().color = new Color(255, 255, 255, 100);
            isMenu = false;
        }
    }

    void Update()
    {
        // 监听聊天文字输入
        ListenTextIn();
    }

    /// <summary>
    /// 聊天面板文字输入
    /// </summary>
    void ListenTextIn()
    {
        if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.KeypadEnter))
        {
            if (msg != "")
            {
                // 发消息给服务器
                SendInfo();
                // 清空消息输入框
                iFMessage.text = "";
                if (!isMenu)
                {
                    // 隐藏聊天面板
                    Hide(0.2f);
                    EventSystem.current.SetSelectedGameObject(null);
                    // 恢复对角色的控制
                    UserControl.currentControl = true;
                }
            }
            else if(!isMenu)
            {
                if (UserControl.currentControl)
                {
                    Show();
                    EventSystem.current.SetSelectedGameObject(iFMessage.gameObject);
                    UserControl.currentControl = false;
                }
                else
                {
                    Hide(0.2f);
                    EventSystem.current.SetSelectedGameObject(null);
                    UserControl.currentControl = true;
                }
            }
        }
    }

    /// <summary>
    /// 显示消息到textChat
    /// </summary>
    public void ShowInfo(string username, string msg)
    {
        if (textChat.text != "")
            textChat.text += "\n";
        // 设置用户名颜色
        string strColor = "<color=blue>";
        if (username == "Server")
            strColor = "<color=red>";
        else if (username == userName)
            strColor = "<color=green>";
        // 显示消息
        textChat.text += strColor + username + ": " + "</color> " + msg;
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
    /// 设置用户名
    /// </summary>
    public void SetUserName(string name)
    {
        userName = name;
    }

    /// <summary>
    /// 显示聊天面板
    /// </summary>
    public void Show()
    {
        canvasGroup.alpha = 1;
        canvasGroup.interactable = true;
        canvasGroup.blocksRaycasts = true;
    }

    /// <summary>
    /// 隐藏聊天面板
    /// </summary>
    public void Hide(float a)
    {
        canvasGroup.alpha = a;
        canvasGroup.interactable = false;
        canvasGroup.blocksRaycasts = false;
    }

    /// <summary>
    /// 脚本的生命周期结束时
    /// </summary>
    void OnDestroy()
    {
        _instance = null;
    }
}
