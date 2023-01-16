// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReloadActor.generated.h"

class UARPin;


UCLASS()
class UE5_AR_API AReloadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReloadActor();

	//function for setting up the actor for plane tracking...
	void SetupActor();

	//components for setting up the reload actor
	UPROPERTY(Category = "Reload Actor Info", VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(Category = "Reload Actor Mesh", VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ReloadMeshComponent;
	
	UARPin* PinComponent;

	FTransform ActorRelTran;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
