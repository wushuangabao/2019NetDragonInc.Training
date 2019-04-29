using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class TriggerThrow : MonoBehaviour
{
    public Image star;

    void Start()
    {
        
    }

    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            CoconutThrower.canThrow = true;
            star.enabled = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            CoconutThrower.canThrow = false;
            star.enabled = false;
        }
    }
}
