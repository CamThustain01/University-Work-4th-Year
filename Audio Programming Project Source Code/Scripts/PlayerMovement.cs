using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{

    [Header("Movement")]
    public float moveSpeed;

    public float groundDrag;

    public float jumpForce;
    public float jumpCooldown;
    public float airMultiplier;
    bool readyToJump;

    [Header("Keybinds")]
    public KeyCode jumpKey = KeyCode.Space;

    [Header("Ground Check")]
    public float playerHeight;
    public LayerMask whatIsGround;
    bool Grounded;

    public Transform orientation;

    float horizontalInput;
    float verticalInput;

    Vector3 moveDirection;

   private bool bIsWalking = false; 

    Rigidbody rb;

    float timeElapsed = 0;


    public AK.Wwise.Event footstepSound = new  AK.Wwise.Event();


    private bool bHasCollidedWater = false;
   

    // Start is called before the first frame update
    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        rb.freezeRotation = true;
    }


    // Update is called once per frame
    private void Update()
    {

        //ground check 
        Grounded = Physics.Raycast(transform.position, Vector3.down, playerHeight * 0.5f + 0.2f, whatIsGround);

        timeElapsed += Time.deltaTime;

        MyInput();
        SpeedControl();

        //handle drag
        if(Grounded)
        {
            rb.drag = groundDrag;
        }
        else
        {
            rb.drag = 0;
        }

       

    }

    private void FixedUpdate()
    {
        MovePlayer();
        
    }

    private void MyInput()
    {
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");
        //footstepSound.Post(gameObject);

        PlayFootstep();

        //when to jump 
        if (Input.GetKey(jumpKey) && readyToJump && Grounded)
        {
            readyToJump = false;

            Jump();

            Invoke(nameof(ResetJump), jumpCooldown);
        }

    }

    private void MovePlayer()
    {
        //calculate player movement

        moveDirection = orientation.forward * verticalInput + orientation.right * horizontalInput;

        
        //on ground
        if (Grounded)
        {
            rb.AddForce(moveDirection.normalized * moveSpeed * 10f, ForceMode.Force);
           // bIsWalking = true;
            //footstepSound.Post(gameObject);
        }
      
        //in air 
        else if(!Grounded)
        {
          rb.AddForce(moveDirection.normalized * moveSpeed * 10f * airMultiplier, ForceMode.Force);
           // footstepSound.Post(gameObject);
        }

        
       
       
    }

    private void SpeedControl()
    {
        Vector3 flatVel = new Vector3(rb.velocity.x, 0f, rb.velocity.z);

        //limit velocity if needed
        if(flatVel.magnitude > moveSpeed)
        {
            Vector3 limitedVel = flatVel.normalized * moveSpeed;
            rb.velocity = new Vector3(limitedVel.x, rb.velocity.y, limitedVel.z);
        }
    }

    private void Jump()
    {
        //reset y velocity

        rb.velocity = new Vector3(rb.velocity.x, 0f, rb.velocity.z);

        rb.AddForce(transform.up * jumpForce, ForceMode.Impulse);

    }

    private void ResetJump()
    {
        readyToJump = true;
    }

    private void PlayFootstep()
    {
        if(rb.velocity.magnitude > moveSpeed - 0.5 && timeElapsed > 0.4) //velocity value will need to be changed if players speed is changed.
        {
            // Debug.Log("Footsteps"); for debugging
            // AkSoundEngine.SetSwitch("FootstepTerrain", "Grass", gameObject);
           // FootstepSwitch();
            Debug.Log("Grass Footsteps");
            footstepSound.Post(gameObject);
            timeElapsed = 0;

            

        }
    }

    private void OnTriggerEnter(Collider other)
    {

        if (other.gameObject.tag == "Water")
        {
            AkSoundEngine.SetSwitch("FootstepTerrain", "Water", gameObject);
            Debug.Log("Water");
        }
        if (other.gameObject.tag == "Cave")
        {
            AkSoundEngine.SetSwitch("FootstepTerrain", "Stone", gameObject);
            Debug.Log("Stone");
        }

        if (other.gameObject.tag == "Grass")
        {
            AkSoundEngine.SetSwitch("FootstepTerrain", "Grass", gameObject);
            Debug.Log("Grass");
        }
    }


   /* private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag == "Ground")
        {
            AkSoundEngine.SetSwitch("FootstepTerrain", "Grass", gameObject);
            Debug.Log("Grass");
        }
    }*/

}
