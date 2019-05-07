using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class DoorOutPost: MonoBehaviour
{
    public AudioClip soundOpen;
    public AudioClip soundShut;

    // 关门所等待时间: 玩家离开触发器 -> 门自动关闭
    public float timeWait = 1.5f;

    bool playerInTrigger = false;
    bool doorIsOpen = false;
    float timer = 0.0f;

    void Start()
    {
        
    }

    void Update()
    {
        // 计时与关门
        if (doorIsOpen && !playerInTrigger)
        {
            timer += Time.deltaTime;
            if (timer > timeWait)
            {
                Door(soundShut, false, "doorshut");
                timer = 0.0f;
            }
        }
    }

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.tag == "Player")
        {
            if(!doorIsOpen)
                DoorCheck();
            playerInTrigger = true;
        }
    }

    void OnTriggerExit(Collider col)
    {
        if (col.gameObject.tag == "Player")
        {
            playerInTrigger = false;
        }
    }

    // 检查门是否打开。若没有打开则打开
    void DoorCheck()
    {
        if (!doorIsOpen)
        {
            if (Generator.fullPower)
            {
                Door(soundOpen, true, "dooropen");
            }
            else
            {
                TextHint.SetHint("这扇门好像是电动的...",3.0f);
            }
        }
    }

    // 开门/关门
    void Door(AudioClip aClip, bool openCheck,string animName)
    {
        GetComponent<AudioSource>().PlayOneShot(aClip);
        doorIsOpen = openCheck;
        transform.parent.gameObject.GetComponent<Animation>().Play(animName);
    }
}
