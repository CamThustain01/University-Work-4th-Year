// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomARPawn.h"
#include "CustomGameState.h"
#include "CustomActor.h"

#include "ARPin.h"
#include "ARBlueprintLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlaceableActor.h"
#include "ReloadActor.h"
#include "PowerupActor.h"

ACustomGameMode::ACustomGameMode():
	SpawnedActor(nullptr)
{
	// Add this line to your code if you wish to use the Tick() function
	PrimaryActorTick.bCanEverTick = true;

	// Set the default pawn and gamestate to be our custom pawn and gamestate programatically
	DefaultPawnClass = ACustomARPawn::StaticClass();
	GameStateClass = ACustomGameState::StaticClass();
	
}


void ACustomGameMode::StartPlay() 
{
	SpawnInitialActors();

	// This is called before BeginPlay
	StartPlayEvent();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current Score: %d"), GetScore()));

	arManager = GWorld->SpawnActor<AHelloARManager>();//initalises hello ar manager 

	//initialise game state pointer
	auto GetGS = GetWorld()->GetGameState();
	Gamestate_ = Cast<ACustomGameState>(GetGS);

	// This function will transcend to call BeginPlay on all the actors 
	Super::StartPlay();
	

}

void ACustomGameMode::StartCountdown() //function for starting countdown, will start a timer which starts the countdown.
{
	FTimerHandle THandle;
	//if level has began start timer
	GetWorldTimerManager().SetTimer(THandle,this,&ACustomGameMode::LevelCountdown,1.0f,true,0.0);
}

void ACustomGameMode::LevelCountdown()
{
	if(SecondsRemaining > 0 ) //if the seconds greater than 0 take one away from seconds
	{
		SecondsRemaining--;
	}
	else
	{
		if(MinutesRemaining == 0) //if minutes equals 0 do the following
		{
			//players wins switch to win state
			bLevelWon = true;
		}
		else //if minutes is not 0 take 1 away from minutes and set seconds to 59
		{
			MinutesRemaining--;
			SecondsRemaining = 59;
		}
	}
}

void ACustomGameMode::CheckPlayerHealth()
{
	if(Gamestate_->PlayerHealth <= 0.0f)//check if players health is less than or equal to 0
		{
			bLevelLost = true; // set level lost boolean to true if so...
		}
}


// An implementation of the StartPlayEvent which can be triggered by calling StartPlayEvent() 
void ACustomGameMode::StartPlayEvent_Implementation() 
{
	// Start a timer which will call the SpawnCube Function every 4 seconds
	//GetWorldTimerManager().SetTimer(Ticker, this, &ACustomGameMode::SpawnCube, 4.0f, true, 0.0f);
}



void ACustomGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ACustomGameMode::SpawnInitialActors()
{

	// Spawn an instance of the HelloARManager class

}

void ACustomGameMode::LevelBegunSetup()
{
	arManager->StopTracking();//stops plane tracking	
}


void ACustomGameMode::LineTraceSpawnActor(FVector ScreenPos)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Line Trace Reached"));

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
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("ARPin is valid"));
				//If the pin is valid 
				auto PinTF = ActorPin->GetLocalToWorldTransform();
				//Spawn a new Actor at the location if not done yet
				if (!SpawnedActor)
				{
					//set up parameters for placeable level
					const FActorSpawnParameters SpawnInfo;
					const FRotator MyRot(0, 0, 0); 
					const FVector MyLoc(0, 0, 0);
					SpawnedActor = GetWorld()->SpawnActor<APlaceableActor>(PlacableToSpawn,MyLoc, MyRot, SpawnInfo);//spanws level 
					SpawnedActor->SetActorTransform(PinTF);
					SpawnedActor->PinComponent = ActorPin;

					
				}

				//Spawn a new Reload Actor at the location if not done yet
				if (!ReloadActor)
				{
					//sets up parameters for reload actor
					const FActorSpawnParameters SpawnInfo;
					const FRotator MyRot(0, 0, 0);
					const FVector MyLoc(0, 0, 150);
					ReloadActor = GetWorld()->SpawnActor<AReloadActor>(ReloadActorToSpawn,MyLoc, MyRot, SpawnInfo); //spawns reload actor
					ReloadActor->SetActorTransform(PinTF);
					ReloadActor->PinComponent = ActorPin;
	
				}
				//Spawn a powerup actor at location
				if (!PowerupActor)
				{
					const FActorSpawnParameters SpawnInfo;
					const FRotator MyRot(0, 0, 0);
					const FVector MyLoc(0, 0, 150);
					PowerupActor = GetWorld()->SpawnActor<APowerupActor>(PowerupActorToSpawn,MyLoc, MyRot, SpawnInfo); //spawns powerup actor
					PowerupActor->SetActorTransform(PinTF);
					PowerupActor->PinComponent = ActorPin;
					
					
					
					
	
				}
			
			}
			// IF ARPins are Not supported locally (for iOS Devices) We will spawn the object in the location where the line trace has hit
			else{
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("ARPin is invalid"));
				//Spawn a new Actor at the location if not done yet
				if (!SpawnedActor)
				{
					const FActorSpawnParameters SpawnInfo;
					const FRotator MyRot(0, 0, 0);
					const FVector MyLoc(0, 0, 0);
					SpawnedActor = GetWorld()->SpawnActor<APlaceableActor>(PlacableToSpawn, MyLoc, MyRot, SpawnInfo);
				}
				SpawnedActor->SetActorTransform(TrackedTF);
				SpawnedActor->SetActorScale3D(FVector(0.2, 0.2, 0.2));


			}
		}
	}
}

