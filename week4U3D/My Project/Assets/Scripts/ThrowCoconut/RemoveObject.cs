using System.Collections;
using UnityEngine;

public class RemoveObject : MonoBehaviour
{
    public float timeExist = 3.0f;

    void Start()
    {
        Destroy(gameObject, timeExist);
    }

    void Update()
    {
        
    }
}
