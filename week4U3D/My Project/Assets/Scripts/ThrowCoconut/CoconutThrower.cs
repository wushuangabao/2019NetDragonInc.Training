using System.Collections;
using UnityEngine;

public class CoconutThrower : MonoBehaviour
{
    static public bool canThrow = false;

    public float speedThrow = 1000.0f;
    public GameObject prefabCoconut;

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(canThrow && Input.GetButtonDown("Fire1"))
        {
            GameObject newCoconut = GameObject.Instantiate(prefabCoconut, transform.position, transform.rotation) as GameObject;
            newCoconut.name = "Coconut";
            Vector3 b = newCoconut.transform.TransformDirection(Vector3.forward);
            newCoconut.GetComponent<Rigidbody>().AddForce(b * speedThrow);
            gameObject.GetComponent<AudioSource>().Play();
        }
    }
}
