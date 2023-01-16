// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AREnemyCharacter.h"
#include "CustomARPawn.h"
#include "CustomGameState.h"
#include "EnemyManagement.generated.h"

UCLASS()
class UE5_AR_API AEnemyManagement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagement();
	
	ACustomGameState* GameState;
	
	UFUNCTION(BlueprintCallable)
	virtual void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	virtual void SpawnEndless();

	//uproperty for choosing enemy in editor
	UPROPERTY(Category="Pick Enemy Char",EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AAREnemyCharacter> PickEnemy;

	//creates boolean for checking if target has been reached by enemies
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bTargetReached = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle Ticker;

	//create instances of enemy
	AAREnemyCharacter* Enemy_;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
