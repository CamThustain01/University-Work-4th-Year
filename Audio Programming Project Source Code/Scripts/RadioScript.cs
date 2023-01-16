using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RadioScript : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject radio;
    public AK.Wwise.Event PlaySound = new AK.Wwise.Event();
    void Start()
    {
        //PlaySound.Post(radio);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag =="Player")
        {
           Debug.Log("Play Radio!");
           PlaySound.Post(radio);
           
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if(other.gameObject.tag =="Player")
        {
            Debug.Log("Stop Radio!");
            PlaySound.Stop(radio);
        }
    }
}
