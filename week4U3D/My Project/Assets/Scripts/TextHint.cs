using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class TextHint : MonoBehaviour
{
    static float timeShow = 3.0f;
    static Text textHint;
    static bool isShow = false;

    float timer = 0.0f;

    void Start()
    {
        textHint = gameObject.GetComponent<Text>();
    }

    void Update()
    {
        // 计时，若到期则去除文字
        if (isShow)
        {
            timer += Time.deltaTime;
            if (timer > timeShow)
            {
                textHint.text = "";
                timer = 0.0f;
                isShow = false;
            }
        }
    }

    // 设置提示文字和提示持续时间
    static public void SetHint(string message,float time = 3.0f)
    {
        // case:正在显示上一条提示
        if (isShow)
            return; //todo优化

        textHint.text = message;
        timeShow = time;
        isShow = true;
    }
}
