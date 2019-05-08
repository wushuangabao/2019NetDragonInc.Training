using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class EnterGame : MonoBehaviour
{
    public Button btnOffline;
    public Button btnOnline;
    public InputField iFUserName;
    public InputField iFPassWord;
    public CanvasGroup loginPanel;
    public Text textBtnOffline;
    public Text textBtnOnline;

    string userName = "";
    string passWord = "";
    bool startTimer = false;
    float timer = 0.0f;

    void Start()
    {
        btnOffline.onClick.AddListener(delegate
        {
            if (textBtnOffline.text == "开始游戏")
            {
                // 进入联机模式
                if (Client.Instance.LoginRoom())
                {
                    SceneManager.LoadScene("Island");
                    Client.Instance.EnterIsland();
                }
                else
                {
                    textBtnOffline.text = "请先登录！";
                    startTimer = true;
                }
            }
            else
            {
                // 进入单机模式
                Client.Instance.Dispose();
                SceneManager.LoadScene("Island");
            }
        });

        btnOnline.onClick.AddListener(delegate
        {
            if(textBtnOnline.text == "联机模式")
            {
                ShowLoginPanel(false);
                ChatPanel.Instance.Show();
                Client.Instance.StartClient(userName, passWord);
                textBtnOffline.text = "开始游戏";
                textBtnOnline.text = "重新登录";
            }
            else
            {
                ChatPanel.Instance.Hide(0);
                ShowLoginPanel(true);
                textBtnOffline.text = "单机模式";
                textBtnOnline.text = "联机模式";
            }
        });

        iFUserName.onValueChanged.AddListener(delegate
        {
            userName = iFUserName.text;
        });

        iFPassWord.onValueChanged.AddListener(delegate
        {
            passWord = iFPassWord.text;
        });
    }

    void Update()
    {
        if (startTimer)
        {
            timer += Time.deltaTime;
            if (timer > 1)
            {
                startTimer = false;
                timer = 0.0f;
                if(textBtnOffline.text == "请先登录！")
                    textBtnOffline.text = "开始游戏";
            }
        }
    }

    // 显示/隐藏登录面板
    void ShowLoginPanel(bool show)
    {
        loginPanel.alpha = show ? 1.0f : 0;
        loginPanel.interactable = show;
        loginPanel.blocksRaycasts = show;
    }
}
