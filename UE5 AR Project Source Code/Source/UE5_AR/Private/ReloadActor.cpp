// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadActor.h"
#include "ARPin.h"

// Sets default values
AReloadActor::AReloadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	//setsup reload mesh 
	ReloadMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ReloadMeshComponent->SetupAttachment(SceneComponent);

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	ReloadMeshComponent->SetStaticMesh(MeshAsset.Object);
}

void AReloadActor::SetupActor()
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
void AReloadActor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AReloadActor::Tick(float DeltaTime)
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

			// Scale down default cube mesh - Change this for your applications.
			//SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
			break;

		case EARTrackingState::NotTracking:
			PinComponent = nullptr;

			break;

		}
	}
}

