using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Shoot : MonoBehaviour
{
    public float moveSpeed = 15f;   //左右移动速度
    public float rotateSpeed = 25f; //上下旋转速度
    public float powerPerTime = 5f; //每次update时间内蓄力增加的力
    public float powerInit = 100f;  //初始力
    public int timePressMax = 100;  //最长蓄力帧数
    public Rigidbody bullet;
    public int count = 50;   //泥巴总数

    int timePress = 0;     //鼠标按下的时间
    float angle = 0;         //俯仰角度
    float angleOld = 0;
    bool isPress = false;

    void Update()
    {
        // 移动摄像机
        float dh = Input.GetAxis("Horizontal") * Time.deltaTime * moveSpeed,
            da = Input.GetAxis("Vertical") * Time.deltaTime * rotateSpeed,
            x = transform.position.x + dh;
        angle -= da;
        if (x > -15.5 && x < 15.5)
            transform.Translate(dh, 0, 0);
        if (angle > -25 && angle < 10)
        {
            transform.Rotate(Vector3.right, -da);
            angleOld = angle;
        }
        else
            angle = angleOld;

        // 鼠标左键按下 蓄力
        if (Input.GetMouseButtonDown(0))
            isPress = true;
        if (isPress && timePress<timePressMax)
        {
            timePress++;
            GameObject.Find("Canvas/Press").GetComponent<Text>().text = "蓄力" + timePress + "帧";
        }

        // 鼠标左键释放 发射
        if (Input.GetMouseButtonUp(0) && count>0)
        {
            float power = powerPerTime * timePress + powerInit;
            Rigidbody instance = (Rigidbody)Instantiate(bullet, transform.position, transform.rotation);
            Vector3 fwd = transform.TransformDirection(Vector3.forward);
            instance.AddForce(fwd * power);
            
            timePress = 0;
            isPress = false;
            count--;
            GameObject.Find("Canvas/Count").GetComponent<Text>().text = "还剩" + count + "块泥巴";
        }
    }
}
