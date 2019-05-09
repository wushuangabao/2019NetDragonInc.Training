using System;
using UnityEngine;
using UnityStandardAssets.CrossPlatformInput;

[RequireComponent(typeof(CharacterControl))]
public class UserControl : MonoBehaviour
{
    // 是否具有人物控制权
    public static bool currentControl = true;

    // 加入MouseLook功能
    [SerializeField] private MouseLook m_MouseLook;

    private CharacterControl m_Character;
    private Transform m_Cam;
    private Vector3 m_CamForward;
    private Vector3 m_Move;
    private bool m_Jump;


    private void Start()
    {
        m_Cam = Camera.main.transform;
        m_Character = GetComponent<CharacterControl>();
        m_MouseLook.Init(transform, Camera.main.transform);
    }


    private void Update()
    {
        if (currentControl)
        {
            // 更新MouseLook的角度
            m_MouseLook.LookRotation(transform, Camera.main.transform);

            // 检测是否开始跳跃
            if (!m_Jump)
            {
                m_Jump = CrossPlatformInputManager.GetButtonDown("Jump");
            }
        }
    }


    // 物理引擎中用FixedUpdate代替Update，它的时间固定，不受帧率影响
    private void FixedUpdate()
    {
        if (!currentControl)
            return;

        // 读取输入
        float v = CrossPlatformInputManager.GetAxis("Vertical");
        bool crouch = Input.GetKey(KeyCode.C);

        // 计算角色移动的方向
        if (m_Cam != null)
        {
            // calculate camera relative direction to move:
            m_CamForward = Vector3.Scale(m_Cam.forward, new Vector3(1, 0, 1)).normalized;
            m_Move = v * m_CamForward;
        }
        else
        {
            // use world-relative directions in the case of no main camera
            m_Move = v * Vector3.forward;
        }

        if (Client.Instance.enterIsland)
        {
            // 将操作参数发送到服务器
            if(m_Move.x!=0 || m_Move.y != 0 || m_Move.z != 0 || crouch!=false || m_Jump!=false)
                Client.Instance.Manipulate(m_Move, crouch, m_Jump);
        }
        else
            // 将参数传递到CharacterControl脚本
            m_Character.Move(m_Move, crouch, m_Jump);

        m_Jump = false;

        // 更新鼠标锁
        m_MouseLook.UpdateCursorLock();
    }

}
