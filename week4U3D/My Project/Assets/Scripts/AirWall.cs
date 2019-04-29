using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class AirWall : MonoBehaviour
{
    public Text textHint;
    public float timeHintShow = 4.0f;

    void Start()
    {
        
    }


    void Update()
    {
        
    }

    void OnCollisionEnter(Collision col)
    {
        if (col.collider.gameObject.tag == "Player")
        {
            SetHint("不能再往外了，小心掉海里...");
            StartCoroutine("ShowTextHint");
        }
    }

    void SetHint(string message)
    {
        textHint.text = message;
        if (!textHint.enabled)
        {
            textHint.enabled = true;
        }
    }

    IEnumerator ShowTextHint()
    {
        yield return new WaitForSeconds(timeHintShow);
        textHint.enabled = false;
    }
}
