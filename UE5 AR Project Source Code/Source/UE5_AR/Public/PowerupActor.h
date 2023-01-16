// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerupActor.generated.h"

class UARPin;


UCLASS()
class UE5_AR_API APowerupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerupActor();

	void SetupActor();

	//components for setting up the powerup actor
	UPROPERTY(Category = "Powerup Actor Info", VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(Category = "Powerup Actor Mesh", VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PowerupMeshComponent;
	
	UARPin* PinComponent;

	//f transform for calculating the relative transform of the actor
	FTransform ActorRelTran;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
//ticker for timer
	FTimerHandle Ticker;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPowerupVisible(); //function which sets powerup visible
	void BeginPowerupTimer();//function which starts timer and calls powerup visible function.
	void ActivatePowerup(bool &Active);//activate powerup function
	
	

};
