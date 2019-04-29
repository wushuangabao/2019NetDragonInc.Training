using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class Generator : MonoBehaviour
{
    public Texture[] textureGenerator;
    public Light[] lightDoor;

    public AudioClip soundGetPower;
    public AudioClip soundGetFullPower;

    public Image imageCell;
    public GameObject door;

    static public bool fullPower = false;

    int charge = 0; //发电机获得的电池数量
    int spark = 5;  //门口灯开启时闪烁的次数

    void Start()
    {
        
    }

    void Update()
    {
        
    }

    void OnCollisionEnter(Collision other)
    {
        if (other.collider.gameObject.tag == "Player" && charge < 4)
        {
            if (Inventory.charge < 4)
            {
                if(charge < Inventory.charge)
                {
                    TextHint.SetHint("给设备装上了新电池...", 3.0f);
                    charge = Inventory.charge;
                    GetComponent<AudioSource>().PlayOneShot(soundGetPower);
                    transform.Find("chargeMeter").GetComponent<Renderer>().material.mainTexture = textureGenerator[Inventory.charge];
                }
                else
                    TextHint.SetHint("这台设备的电量还不够多...", 3.5f);
            }
            if (Inventory.charge >= 4)
            {
                TextHint.SetHint("装上这些电池应该足够了...", 3.0f);
                charge = 4;
                GetComponent<AudioSource>().PlayOneShot(soundGetPower);
                StartCoroutine("getFullPower"); //开启协程
                imageCell.enabled = false;      //去掉电池UI
            }
        }
    }

    IEnumerator getFullPower()
    {
        transform.Find("chargeMeter").GetComponent<Renderer>().material.mainTexture = textureGenerator[4];
        StartCoroutine("TurnOnLight");

        yield return new WaitForSeconds(spark * 0.59f);

        fullPower = true;
        TextHint.SetHint("门已经开了！", 2.0f);
        GameObject.Find("door").SendMessage("DoorCheck");
    }

    IEnumerator TurnOnLight()
    {
        int i = 0;

        // 获取门灯的点光源数目
        int len = lightDoor.Length;

        // 门灯闪烁，门发出声音
        for(int j = 0; j < spark; j++)
        {
            door.GetComponent<AudioSource>().Play();

            for (i = 0; i < len; i++)
                lightDoor[i].color = Color.green;
            yield return new WaitForSeconds(0.29f);

            for (i = 0; i < len; i++)
                lightDoor[i].color = Color.red;
            yield return new WaitForSeconds(0.2f);
        }

        // 门灯变绿
        for (i = 0; i < len; i++)
            lightDoor[i].color = Color.green;
    }
}
