// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include "CustomARPawn.generated.h"

class UCameraComponent;

UCLASS()
class UE5_AR_API ACustomARPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomARPawn();

	bool getLevelState();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnScreenTouch(const ETouchIndex::Type FingerIndex, const FVector ScreenPos);
	virtual void OnScreenHold(const ETouchIndex::Type FingerIndex, const FVector ScreenPos);

	void Shoot();
	void SetPowerupBool();
	
	bool WorldHitTest(FVector2D touchPos, FHitResult& hitResult);
	//bool for level active 
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		bool levelBegun = false;

	FTimerHandle PuTicker;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraComponent;
		//property for picking weapon 	
	UPROPERTY(Category = "myCategory", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AGameWeapon> PickProjectile; 

	
	
	//uproperty for weapon ammo can be changed in editor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int WeaponAmmo = 20;

	
private:
	
	UMaterialInstance* redMat;
	UMaterialInstance* whiteMat;

	USoundBase* ShootSound;//some game sfx
	USoundBase* ReloadSound;
	USoundBase* PowerupSound;

	//creates instances of actors
	class APlaceableActor* PlaceableActor;
	class AReloadActor* ReloadActor;
	class APowerupActor* PowerupActor;
	//class AGameWeapon* Weapon;
	AGameWeapon* Weapon_;

	//boolean for timer
	bool bTimerStarted = false;
	//boolean for powerup
	bool bPowerupIsActive = false;
};


