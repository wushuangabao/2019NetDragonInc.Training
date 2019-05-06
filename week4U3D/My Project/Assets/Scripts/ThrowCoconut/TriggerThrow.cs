using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class TriggerThrow : MonoBehaviour
{
    public Image star;
    public GameObject pointEyes;
    public GameObject pointCamera;
    public Camera mainCamera;
    public bool onTrigger = true;

    private void OnTriggerEnter(Collider other)
    {
        if (onTrigger && other.gameObject.tag == "Player")
        {
            CoconutThrower.canThrow = true;
            star.enabled = true;
            mainCamera.transform.position = pointEyes.transform.position;
            Cursor.lockState = CursorLockMode.Locked;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            ExitThrow();
        }
    }

    public void ExitThrow()
    {
        CoconutThrower.canThrow = false;
        star.enabled = false;
        mainCamera.transform.position = pointCamera.transform.position;
        Cursor.lockState = CursorLockMode.None;
    }
}
