// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARPawn.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "ARBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "CustomGameMode.h"
#include "PlaceableActor.h"
#include "GameWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ARPlaneActor.h"
#include "ARPin.h"
#include "ReloadActor.h"
#include "PowerupActor.h"
#include "Components/AudioComponent.h"

// Sets default values
ACustomARPawn::ACustomARPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SetRootComponent(CameraComponent);

	//set sound bases to the audio source we are trying to play
	ShootSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("SoundCue'/Game/Assets/Audio/shoot_sfx_Cue.shoot_sfx_Cue'")).Object;
	ReloadSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("SoundCue'/Game/Assets/Audio/reload_Cue.reload_Cue'")).Object;
	PowerupSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("SoundCue'/Game/Assets/Audio/powerup_Cue.powerup_Cue'")).Object;
	
	redMat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Assets/Materials/Red_Inst.Red_Inst'")).Object;
	whiteMat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Assets/Materials/White_Inst.White_Inst'")).Object;
}

bool ACustomARPawn::getLevelState()
{
	return levelBegun;
}

// Called when the game starts or when spawned
void ACustomARPawn::BeginPlay()
{
	Super::BeginPlay();
	UARSessionConfig* Config = NewObject<UARSessionConfig>();
	UARBlueprintLibrary::StartARSession(Config);
}

// Called every frame
void ACustomARPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(levelBegun == true) //checks every frame if level is active if so planes are hidden
	{
		TArray<AActor*>actors;
		UGameplayStatics::GetAllActorsOfClass(this,AARPlaneActor::StaticClass(),actors);

		for(auto it : actors) //iterates through actors casts plane actor to the current iteration 
		{
			AARPlaneActor* arPlane = Cast<AARPlaneActor>(it);
			arPlane->SetTrackingState(EARTrackingState::NotTracking); //sets tracking to not tracking
			
		}
	}


	if(levelBegun && !bTimerStarted)
	{
		auto Temp = GetWorld()->GetAuthGameMode();
		auto GM = Cast<ACustomGameMode>(Temp);
		GM->LevelBegunSetup();//stops all plane tracking
		bTimerStarted = true; //start timer
		GM->StartCountdown(); //starts countdown
		
	}
	
}

// Called to bind functionality to input
void ACustomARPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind various player inputs to functions
	// There are a few types - BindTouch, BindAxis, and BindEvent.  
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACustomARPawn::OnScreenTouch);
	PlayerInputComponent->BindTouch(IE_Repeat, this, &ACustomARPawn::OnScreenHold);

	
}

void ACustomARPawn::OnScreenHold(const ETouchIndex::Type FingerIndex, const FVector ScreenPos)
{
	
	if(PlaceableActor && !levelBegun)//if there is placeable actor and begin play hasnt been pressed. States are tracking and user can select placeable actor
	{
		TArray<AActor*>actors;
		UGameplayStatics::GetAllActorsOfClass(this,AARPlaneActor::StaticClass(),actors);

		for(auto it : actors)
		{
			AARPlaneActor* arPlane = Cast<AARPlaneActor>(it);
			//sets planes to not tracking on screen hold
			arPlane->SetTrackingState(EARTrackingState::NotTracking);
			
		}
	
	
		//Basic variables for functionality
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		FVector WorldPos;
		FVector WorldDir;

		//Gets the screen touch in world space and the tracked objects from a line trace from the touch
		UGameplayStatics::DeprojectScreenToWorld(playerController, FVector2D(ScreenPos), WorldPos, WorldDir);
		// Notice that this LineTrace is in the ARBluePrintLibrary - this means that it's exclusive only for objects tracked by ARKit/ARCore
		auto TraceResult = UARBlueprintLibrary::LineTraceTrackedObjects(FVector2D(ScreenPos), false, false, false, true);

		//Checks if the location is valid
		if (TraceResult.IsValidIndex(0))
		{
			// Get the first found object in the line trace - ignoring the rest of the array elements
			auto TrackedTF = TraceResult[0].GetLocalToWorldTransform();

			if (FVector::DotProduct(TrackedTF.GetRotation().GetUpVector(), WorldDir) < 0)
			{
				//Spawn the actor pin and get the transform
				UARPin* ActorPin = UARBlueprintLibrary::PinComponent(nullptr, TraceResult[0].GetLocalToWorldTransform(), TraceResult[0].GetTrackedGeometry());

				// Check if ARPins are available on your current device. ARPins are currently not supported locally by ARKit, so on iOS, this will always be "FALSE" 
				if (ActorPin)
				{
					
					//If the pin is valid 
					auto PinTF = ActorPin->GetLocalToWorldTransform();
					//Spawn a new Actor at the location if not done yet
					PlaceableActor->SetActorTransform(PinTF);
					PlaceableActor->PinComponent = ActorPin;
					
				}
			}
		}
	}
}

void ACustomARPawn::Shoot(/*FVector ScreenPos*/)
{
	
	if(WeaponAmmo > 0) //if weapon ammo is greater than 0, player can shoot
	{
	    
		const FActorSpawnParameters SpawnInfo;
		const FRotator Rotation = GetActorRotation();
		const FVector Location = GetActorLocation();
		Weapon_ = GetWorld()->SpawnActor<AGameWeapon>(Location,Rotation,SpawnInfo); //spawns bullet
		UGameplayStatics::PlaySoundAtLocation(this,ShootSound,Location,Rotation);
		WeaponAmmo -= 1; //takes 1 away from total ammo when a bullet is shot
		Weapon_->WeaponDamage = bPowerupIsActive ? 100 : 50; //flag check for weapon damage if flag true damage is 100, if not 25
	}

}

void ACustomARPawn::SetPowerupBool()
{
	bPowerupIsActive = false; //sets boolen to false, damage will go back to normal when this function is called
}

void ACustomARPawn::OnScreenTouch(const ETouchIndex::Type FingerIndex, const FVector ScreenPos)
{
	auto Temp = GetWorld()->GetAuthGameMode();
	auto GM = Cast<ACustomGameMode>(Temp);

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("ScreenTouch Reached"));
	
	if(!levelBegun)//if level begun button hasn't been pressed player can place 
	{
		if(GM)
		{
			// Add call to the line-trace here from the Custom Game Mode
			GM->LineTraceSpawnActor(ScreenPos); //spawns level zone
		}
	}
	
	FHitResult hitTestResult;

	// If nothing is hit
	if(!WorldHitTest(FVector2D(ScreenPos), hitTestResult))
	{
		//UKismetSystemLibrary::PrintString(this, FString(TEXT("Nothing Pressed")), true, true, FLinearColor::Red, 5);

		if(PlaceableActor)    // If an actor is selected
			if (PlaceableActor->GetSelected()) {
				PlaceableActor->SetSelected(false);    // Unselect it
				PlaceableActor->StaticMeshComponent->SetMaterial(0, whiteMat);    // Change material to unselected mat
				PlaceableActor = nullptr;    // Set back to null

			}
		
	}
	
	UClass* hitActorClass = UGameplayStatics::GetObjectClass(hitTestResult.GetActor());

	if(UKismetMathLibrary::ClassIsChildOf(hitActorClass, APlaceableActor::StaticClass()))    // Check if hit actor is a placeable actor
		{
		PlaceableActor = Cast<APlaceableActor>(hitTestResult.GetActor());    // Set selected actor to object hit

		if (!PlaceableActor->GetSelected())    // If not already selected
			{
			PlaceableActor->SetSelected(true);    // Set to selected
			//PlaceableActor->StaticMeshComponent->SetMaterial(0, redMat);    // Change to selected mat

			}
		

		}
	if(UKismetMathLibrary::ClassIsChildOf(hitActorClass, APowerupActor::StaticClass()))
	{
		PowerupActor = Cast<APowerupActor>(hitTestResult.GetActor());
		if(IsValid(PowerupActor))
		{
			//if powerup actor is touched do...
			PowerupActor->ActivatePowerup(bPowerupIsActive); //activate powerup
			GetWorldTimerManager().SetTimer(PuTicker, this, &ACustomARPawn::SetPowerupBool, 5.0f, false);//deactivates powerup after some time.
			UGameplayStatics::PlaySoundAtLocation(this,PowerupSound,PowerupActor->GetActorLocation(),PowerupActor->GetActorRotation()); //plays powerup sound at powerup actors location
		}
	}
	if(UKismetMathLibrary::ClassIsChildOf(hitActorClass, AReloadActor::StaticClass()))
	{
		ReloadActor = Cast<AReloadActor>(hitTestResult.GetActor()); //casts reload actor object to get actor of the hit result
		if(IsValid(ReloadActor))//if reload actor is touched
			{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Reload Touched"));
			WeaponAmmo = 20; //ammo now equals 20.
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, ReloadActor->GetActorLocation(),ReloadActor->GetActorRotation()); //plays reload sfx at the location of the reload actor.
			}
	}
	//Shoot Weapon
	else if (levelBegun == true) //if level has begun player can shoot
	{
		Shoot();
	}
}

bool ACustomARPawn::WorldHitTest(FVector2D touchPos, FHitResult& hitResult) //function which calculates world hit use player controller.
{

	APlayerController* playerConroller = UGameplayStatics::GetPlayerController(this, 0);

	FVector worldPosition;
	FVector worldDirection;

	bool deporjectionSuccess = UGameplayStatics::DeprojectScreenToWorld(playerConroller, touchPos, /*out*/ worldPosition, /*out*/ worldDirection);

	FVector traceEndVector = worldDirection * 1000.f;
	traceEndVector = worldPosition + traceEndVector;

	// Perform line trace
	bool traceSuccess = GetWorld()->LineTraceSingleByChannel(hitResult, worldPosition, traceEndVector, ECollisionChannel::ECC_WorldDynamic);

	return traceSuccess;
	
}
