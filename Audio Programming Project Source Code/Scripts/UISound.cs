using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UISound : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    public void onClick()
    {

        Debug.Log("UI SOUND!");

        AkSoundEngine.PostEvent("ButtonClick", gameObject);
        


    }

}

