using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MultiPlayers : MonoBehaviour
{
    static MultiPlayers _instance;
    static public MultiPlayers Instance { get { return _instance; } }

    bool updateList = false;
    List<string> nameList = new List<string>();
    List<Player> players = new List<Player>();
    List<Dictionary<string, object>> manipulates = new List<Dictionary<string, object>>();

    public GameObject pointBirth; //玩家角色出生点
    public GameObject prefabCharacter; //角色模板

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
    }

    void Start()
    {
        // 将玩家自身的角色加入players队列
        players.Add(GameObject.Find("Character").GetComponent<Player>());
    }

    void FixedUpdate()
    {
        // 更新players队列
        if (updateList)
        {
            int nPlayers= players.Count,
                n = nameList.Count - nPlayers;
            if (n > 0)
            {
                for (int i = 0; i < n; i++)
                {
                    // 实例化一个游戏角色，加入players队列
                    Player player = Instantiate(prefabCharacter).GetComponent<Player>();
                    player.UpdatePosition(pointBirth.transform.position);
                    player.SetName(nameList[nPlayers + i]);
                    players.Add(player);
                    Debug.Log(nameList[nPlayers + i] + "加入了游戏");
                }
            }
            updateList = false;
        }
        int nMnp = manipulates.Count;
        if (nMnp > 0)
        {
            // players执行玩家操作
            for (int i = 0; i < nMnp; i++)
            {
                string name = (string)manipulates[i]["name"];
                players[nameList.IndexOf(name)].Manipulate(manipulates[i]);
            }
            manipulates.Clear();
        }
    }

    /// <summary>
    /// 从服务器读取玩家的操作数据
    /// </summary>
    public void Manipulate(Dictionary<string, object> dict)
    {
        string name = (string)dict["name"];
        if (!nameList.Contains(name))
        {
            updateList = true;
            // 将用户名（角色的唯一标识）加入nameList队列
            nameList.Add(name);
        }
        // 将玩家操作数据保存（游戏对象的操作要放到主线程执行）
        manipulates.Add(dict);
    }
}
