using System.Collections;
using UnityEngine;

public class TargetCollision : MonoBehaviour
{
    public AudioClip soundWin;
    public AudioClip soundHit;
    public AudioClip soundReset;
    public float timeReset = 1.5f;
    public GameObject cell_old;
    public GameObject cell_new;
    public Vector3 positionNew = new Vector3(231.4f, 135.8f, 166.6f);

    bool beHit = false;
    float timer = 0.0f;
    Animation anim;
    static int number = 0;

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
                number--;
            }
        }
    }

    void OnCollisionEnter(Collision collision)
    {
        if(!beHit && collision.gameObject.name == "Coconut")
        {
            AudioSource audioSource = gameObject.GetComponent<AudioSource>();
            audioSource.PlayOneShot(soundHit);
            anim.Play("down");
            beHit = true;
            number++;
            if (number >= 3)
            {
                audioSource.PlayOneShot(soundWin);
                GameObject.Destroy(cell_old);
                cell_new.transform.position = positionNew;
            }
        }
    }
}
