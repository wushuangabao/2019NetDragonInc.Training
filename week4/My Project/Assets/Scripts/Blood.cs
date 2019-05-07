using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class Blood : MonoBehaviour
{
    static Image imgBlood;
    static float timeShow = 0.6f;
    static bool isShow = false;

    float timer = 0.0f;

    void Start()
    {
        imgBlood = gameObject.GetComponent<Image>();
    }

    void Update()
    {
        // 计时，若到期则去除血图
        if (isShow)
        {
            timer += Time.deltaTime;
            if (timer > timeShow)
            {
                imgBlood.enabled = false;
                timer = 0.0f;
                isShow = false;
            }
        }
    }

    static public void ShowBlood(float time = 0.6f)
    {
        if (isShow)
        {
            timeShow += time;
        }
        else
        {
            isShow = true;
            imgBlood.enabled = true;
            timeShow = time;
        }
    }
}
