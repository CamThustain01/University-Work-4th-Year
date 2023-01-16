using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class MenuUI : MonoBehaviour
{


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


   public void PlayButton()
    {
        // SceneManager.LoadScene("SampleScene");
        StartCoroutine(SceneDelay());
        //Debug.Log("Level Loaded");
    }

    public void QuitButton()
    {
        Application.Quit();
    }


    public void HowToPlayButton()
    {
        SceneManager.LoadScene("HowToPlay");
    }

    public void MenuButton()
    {
        StartCoroutine(Delay());
        SceneManager.LoadScene("MainMenu");
    }
    IEnumerator SceneDelay()
    {
        yield return new WaitForSeconds(1.5f);
        SceneManager.LoadScene("SampleScene");
    }

    IEnumerator Delay()
    {
        yield return new WaitForSeconds(1.5f);
    }
}
