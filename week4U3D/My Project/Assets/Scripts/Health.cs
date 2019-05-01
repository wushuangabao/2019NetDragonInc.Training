using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class Health : MonoBehaviour
{
    static Text textHealth;

    void Start()
    {
        textHealth = gameObject.GetComponent<Text>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // 血量减少
    static public void Reduce(int i)
    {
        int blood = int.Parse(textHealth.text);
        blood -= i;
        if (blood > 0)
        {
            textHealth.text = blood.ToString();
        }
        else
        {
            // 死亡处理
        }
    }
}
