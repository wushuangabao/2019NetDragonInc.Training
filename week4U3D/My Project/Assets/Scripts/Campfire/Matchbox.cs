using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class Matchbox : MonoBehaviour
{
    public GameObject weapon;
    public GameObject matchBox;
    public Image imgWeapon;
    public Image imgMatchbox;

    float timer = 0.0f;
    bool openTimer1 = false;
    bool openTimer2 = false;

    void Update()
    {
        if (openTimer1)
        {
            timer += Time.deltaTime;
            if (timer > 2.0f)
            {
                TextHint.SetHint("获得火柴 x1", 0.9f);
                imgMatchbox.enabled = true;
                openTimer2 = true;
                timer = 0.0f;
            }
            if(openTimer2 && timer > 1.0f)
            {
                openTimer1 = false;
                TextHint.SetHint("获得M16 x1", 0.9f);
                imgWeapon.enabled = true;
                GameObject.Destroy(weapon);
                GameObject.Destroy(matchBox);
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            TextHint.SetHint("这里有一盒火柴和一杆M16！", 1.9f);
            openTimer1 = true;
        }
    }
}
