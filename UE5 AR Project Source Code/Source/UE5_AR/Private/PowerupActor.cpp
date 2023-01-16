// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupActor.h"
#include "ARPin.h"
#include "GameWeapon.h"

// Sets default values
APowerupActor::APowerupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);


	PowerupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	PowerupMeshComponent->SetupAttachment(SceneComponent);

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	PowerupMeshComponent->SetStaticMesh(MeshAsset.Object);

	

}

void APowerupActor::SetupActor()
{
	//set pin component to a pin component (my level custom ar pawn)
	//calculate distance from custom ar pawn to this actor
	//create a transform called relative transform
	//set translation of transform to the distance

	FVector Distance = GetActorLocation() - PinComponent->GetLocalToWorldTransform().GetLocation();
	SetActorLocation(PinComponent->GetLocalToWorldTransform().GetLocation() + Distance);
	ActorRelTran = GetActorTransform();
}

// Called when the game starts or when spawned
void APowerupActor::BeginPlay()
{
	Super::BeginPlay();

	PowerupMeshComponent->SetVisibility(false);
	
	BeginPowerupTimer(); //set powerup visible after 10 seconds
}

// Called every frame
void APowerupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PinComponent)
	{
		auto TrackingState = PinComponent->GetTrackingState();
		
		switch (TrackingState)
		{
		case EARTrackingState::Tracking:
			SceneComponent->SetVisibility(true);
			//times relative transform by pin component for reload actor
			SetActorTransform(PinComponent->GetLocalToWorldTransform() * ActorRelTran); //multiply the pin component by the actors relative transform...
			
			break;

		case EARTrackingState::NotTracking:
			PinComponent = nullptr;

			break;

		}
	}
}

void APowerupActor::SetPowerupVisible()
{
	//SetActorHiddenInGame(false);
	PowerupMeshComponent->SetVisibility(true); //set powerup actor to visible
}

void APowerupActor::BeginPowerupTimer() //function for making the powerup visible
{
	//sets time which is calls SetPowerupVisible func after 10 secs
	GetWorldTimerManager().SetTimer(Ticker, this, &APowerupActor::SetPowerupVisible, 10.0f, false);
}

void APowerupActor::ActivatePowerup(bool &Active)
{
	//once powerup has been touched activate
	//set flag to true
	Active = true;

	//make powerup hidden again
	PowerupMeshComponent->SetVisibility(false);
	
	
}



