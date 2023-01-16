using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OcclusionRaycast : MonoBehaviour
{

    public GameObject AudioListener;

    private float MaxDistOcclusion;

    public bool OcclusionOn = false;

    public string RTPC_Name = "RTPC_Occlusion_LoPass";
    public string RTPC_Volume = "RTPC_Occlusion_Volume";


    public float LoPassMax = 1;
    public float VolumeMax = 1;
    public string Listener = "Main Camera";
    
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
