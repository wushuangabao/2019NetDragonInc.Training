using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class TriggerCampfire : MonoBehaviour
{
    public ParticleSystem fire;
    public Image imgMatchbox;
    public AudioSource audioSource;
    public AudioClip soundWin;

    int i = 0;
    float timer = 0.0f;

    void Start()
    {
        
    }

    void Update()
    {
        if (i == 2)
        {
            // 点火
            timer += Time.deltaTime;
            if (timer > 1.0f)
            {
                fire.gameObject.SetActive(true);
                i++;   // i=3
            }
        }
        else if (i == 3)
        {
            // 进入菜单场景
            timer += Time.deltaTime;
            if (timer > 1.0f)
            {
                audioSource.PlayOneShot(soundWin);
                TextHint.SetHint("游戏暂时结束了，后续剧情敬请期待~");
            }
        }
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            switch (i)
            {
                case 0:
                    TextHint.SetHint("太棒了！这里有篝火...");
                    i++;
                    if (imgMatchbox.enabled)
                        Fire();
                    break;
                case 1:
                    if (imgMatchbox.enabled)
                        Fire();
                    else
                        TextHint.SetHint("得想办法点燃它...", 2.0f);
                    break;
            }
        }
    }

    void Fire()
    {
        TextHint.SetHint("你使用了火柴...", 2.0f);
        i++;
    }
}
