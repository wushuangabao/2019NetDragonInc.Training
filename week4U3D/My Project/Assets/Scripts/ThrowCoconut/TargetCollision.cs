using System.Collections;
using UnityEngine;

public class TargetCollision : MonoBehaviour
{
    public AudioClip soundHit;
    public AudioClip soundReset;
    public float timeReset = 1.5f;

    bool beHit = false;
    float timer = 0.0f;
    Animation anim;

    void Start()
    {
        anim = transform.parent.transform.parent.GetComponent<Animation>();
    }

    void Update()
    {
        if (beHit)
        {
            timer += Time.deltaTime;
            if (timer > timeReset)
            {
                timer = 0.0f;
                gameObject.GetComponent<AudioSource>().PlayOneShot(soundReset);
                anim.Play("up");
                beHit = false;
            }
        }
    }

    void OnCollisionEnter(Collision collision)
    {
        if(!beHit && collision.gameObject.name == "Coconut")
        {
            gameObject.GetComponent<AudioSource>().PlayOneShot(soundHit);
            anim.Play("down");
            beHit = true;
        }
    }
}
