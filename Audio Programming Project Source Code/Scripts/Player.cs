using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class Player : MonoBehaviour
{


    private int Collectables;

    public GameObject SecretWall;

    private bool bSecretTrigger = false;
    private bool bDoorClose = false;
    private bool bIsCollected = false;
    


    //public AK.Wwise.Event StopStarSound = new AK.Wwise.Event();
    public AK.Wwise.Event SecretWallOpen = new AK.Wwise.Event();
    public AK.Wwise.Event SecretWallClose = new AK.Wwise.Event();

    public Text countText;

   

    // Start is called before the first frame update
    void Start()
    {
        Collectables = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.E))
        {
           // Debug.Log("You Have:  " + Collectables + "Collectables");
        }

        TriggerSecret();

    
        countText.text = Collectables.ToString();
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag=="Collectable")
        {

            Collectables++;
            other.gameObject.SetActive(false);
            bIsCollected = true;

            
        }

        if(other.gameObject.tag=="Open")
        {
            bSecretTrigger = true;
            SecretWallOpen.Post(other.gameObject);
            other.gameObject.SetActive(false);
            //Debug.Log("Door Open Sound");
        }

        if (other.gameObject.tag == "Close")
        {
            //SecretWall.SetActive(true);
            // bSecretTrigger = true;
            bDoorClose = true;
            SecretWallClose.Post(other.gameObject);
            other.gameObject.SetActive(false);
            Debug.Log("Door Close Sound");
        }

    }

    /*private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Collectable")
        {
            StopStarSound.Stop(other.gameObject);
        }
    }*/


    void TriggerSecret()
    {
        if(Collectables >= 5 && bSecretTrigger == true)
        {
            SecretWall.SetActive(false);

        }
        if(bDoorClose == true)
        {
            SecretWall.SetActive(true);

        }
    }

    public bool ReturnStatus()
    {
        return bIsCollected;
    }

    //public int ReturnCollectables()
    //{
        //return Collectables;
    //}



}
