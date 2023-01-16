// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "GameTimer.generated.h"

UCLASS()
class UE5_AR_API AGameTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateTimer();
	void BeginTimer();
	void CheckTimer();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int TimeRemaining;
	UTextRenderComponent* TimeRemainingText;

	FTimerHandle Ticker;
	
};
