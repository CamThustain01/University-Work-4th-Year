using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StarSound : MonoBehaviour
{
   

    Player player;
    public GameObject Star;
   public AK.Wwise.Event PlaySound = new AK.Wwise.Event();
    // Start is called before the first frame update
    void Start()
    {
        player.GetComponent<Player>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            Debug.Log("Play StarSound");
            PlaySound.Post(Star);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            Debug.Log("Stop StarSound!");
            PlaySound.Stop(Star);
        }
    }

    public void CollectableCheck()
    {
        if(player.ReturnStatus()==true)
        {
           Debug.Log("Stop playing sound");
            //StopSound.Post(gameObject);
        }
    }
}
