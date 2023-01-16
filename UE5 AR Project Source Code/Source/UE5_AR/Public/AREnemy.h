// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AREnemy.generated.h"

UCLASS()
class UE5_AR_API AAREnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAREnemy();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveToTarget(FVector TargetLocation);
	
	int enemyHealth = 100;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> TargetActor;
	
	

};
