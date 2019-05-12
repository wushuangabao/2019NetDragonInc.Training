using System;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    string m_Name = "";
    int health = 100;
    public CharacterControl m_Character;
    float timer = 0;

    void Start()
    {
    }

    void Update()
    {
        try
        {
            if (Client.Instance.enterIsland)
            {
                timer += Time.deltaTime;
                // 每隔0.5秒上传玩家状态数据
                if (timer > 0.5f)
                {
                    timer = 0f;
                    Vector3 position = transform.localPosition,
                        rotation = transform.localEulerAngles;
                    Client.Instance.Upadate(health, position, rotation);
                }
            }
        }
        catch (Exception e)
        {
            Debug.Log("上传状态数据失败：" + e.ToString());
        }
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
        float x = System.Convert.ToSingle(d["moveX"]),
            y = System.Convert.ToSingle(d["moveY"]),
            z = System.Convert.ToSingle(d["moveZ"]);
        Vector3 vectorMove = new Vector3(x, y, z);
        m_Character.Move(vectorMove, (bool)d["c"], (bool)d["j"]);
    }

    public void UpdatePosition(Vector3 positon)
    {
        transform.localPosition = positon;
    }

    public void UpdateState(Dictionary<string, object> d)
    {
        float x = System.Convert.ToSingle(d["pX"]),
            y = System.Convert.ToSingle(d["pY"]),
            z = System.Convert.ToSingle(d["pZ"]);
        Vector3 position = new Vector3(x, y, z);
        x = System.Convert.ToSingle(d["rX"]);
        y = System.Convert.ToSingle(d["rY"]);
            z = System.Convert.ToSingle(d["rZ"]);
        Vector3 rotation = new Vector3(x, y, z);
        //ulong time = (ulong)d["t"];
        health = Convert.ToInt32(d["h"]);
        UpdatePosition(position);
        transform.localEulerAngles = rotation;
    }

}
