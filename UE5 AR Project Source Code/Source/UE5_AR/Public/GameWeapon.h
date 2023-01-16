// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameWeapon.generated.h"

UCLASS()
class UE5_AR_API AGameWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly,Category = Projectile)
		class USphereComponent* CollisionSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
		void onhit(UPrimitiveComponent* HitComp,AActor* actor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
//variable for weapon damage which can be changed in editor 
	UPROPERTY(EditAnywhere)
		float WeaponDamage = 50.0f;
	
	//for setting bullet mesh and material
	UStaticMeshComponent* BulletMesh;

	UMaterialInstance* BulletMat;
};
