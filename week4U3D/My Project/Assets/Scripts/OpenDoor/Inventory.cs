using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class Inventory : MonoBehaviour
{
    public Sprite[] spriteCharge;
    public Image chargeGUI;
    public AudioClip soundPick;

    static public int charge = 0;

    void Start()
    {
        
    }

    void Update()
    {
        
    }

    void CellPick()
    {
        AudioSource.PlayClipAtPoint(soundPick, transform.position);
        charge++;
        if (charge <= 4)
        {
            chargeGUI.sprite = spriteCharge[charge];
        }
    }
}
