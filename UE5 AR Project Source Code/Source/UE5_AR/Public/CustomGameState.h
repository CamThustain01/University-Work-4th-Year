// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameState.generated.h"

/**
 * 
 */
UCLASS()
class UE5_AR_API ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ACustomGameState();
	~ACustomGameState() = default;
	
	//int32 Score;
	//variable for setting players health
UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PlayerHealth = 100.0f;
	

};
