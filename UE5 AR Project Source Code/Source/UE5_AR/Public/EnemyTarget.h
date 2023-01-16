// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomGameState.h"
#include "CustomGameMode.h"
#include "EnemyTarget.generated.h"

class ACustomGameState;

UCLASS()
class UE5_AR_API AEnemyTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyTarget();
	//create instances of gamestate and mode
	ACustomGameState* Gamestate_;
	ACustomGameMode* Gamemode_;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly,Category = Projectile)
	class USphereComponent* CollisionSphere;

	UFUNCTION()
	void onhit(UPrimitiveComponent* HitComp,AActor* actor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);


};
