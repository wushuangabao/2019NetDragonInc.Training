using System.Collections;
using UnityEngine;

public class PowerCell : MonoBehaviour
{
    public float rotationSpeed = 100.0f;

    void Start()
    {
        
    }

    void Update()
    {
        transform.Rotate(new Vector3(0, rotationSpeed * Time.deltaTime, 0));
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            other.gameObject.SendMessage("CellPick");
            Destroy(gameObject);
        }
    }
}
