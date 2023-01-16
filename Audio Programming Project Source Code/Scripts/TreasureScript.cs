using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class TreasureScript : MonoBehaviour
{

    public AK.Wwise.Event TreasureSound = new AK.Wwise.Event();

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


   private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            Debug.Log("Player has collided with treasure");
            TreasureSound.Post(gameObject);
            StartCoroutine(GameEnd());
        }
    }

    IEnumerator GameEnd()
    {
        yield return new WaitForSeconds(4.0f);
        SceneManager.LoadScene("EndScene");
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;
    }

}
