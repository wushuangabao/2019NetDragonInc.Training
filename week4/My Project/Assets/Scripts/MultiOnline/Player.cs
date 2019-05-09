using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    string m_Name = "";
    int health = 100;
    CharacterControl m_Character;

    void Start()
    {
        m_Character = GetComponent<CharacterControl>();
    }

    void Update()
    {
        
    }

    public string GetName()
    {
        return m_Name;
    }

    public void SetName(string name)
    {
        m_Name = name;
    }

    public void Manipulate(Dictionary<string, object> d)
    {
        Vector3 vectorMove = new Vector3((int)d["moveX"], (int)d["moveY"], (int)d["moveZ"]);
        m_Character.Move(vectorMove, (bool)d["c"], (bool)d["j"]);
    }

    public void UpdatePosition(Vector3 positon)
    {
        transform.localPosition = positon;
    }

    public void UpdateState(Dictionary<string, object> d)
    {
        health = (int)d["h"];
        float[] position = (float[])d["p"];
        float[] rotation = (float[])d["r"];
        ulong time = (ulong)d["t"];

        UpdatePosition(new Vector3(position[0], position[1], position[2]));
        transform.localEulerAngles = new Vector3(rotation[0], rotation[1], rotation[2]);
    }

}
