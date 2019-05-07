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

    void Start()
    {
        btnOffline.onClick.AddListener(delegate
        {
            SceneManager.LoadScene("Island");
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
            
            // SceneManager.LoadScene("Island");
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

    // 显示/隐藏登录面板
    void ShowLoginPanel(bool show)
    {
        loginPanel.alpha = show ? 1.0f : 0;
        loginPanel.interactable = show;
        loginPanel.blocksRaycasts = show;
    }
}
