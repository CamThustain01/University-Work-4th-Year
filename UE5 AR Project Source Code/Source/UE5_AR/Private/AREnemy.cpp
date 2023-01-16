// Fill out your copyright notice in the Description page of Project Settings.


#include "AREnemy.h"
#include "CustomActor.h"


// Sets default values
AAREnemy::AAREnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AAREnemy::BeginPlay()
{
	
	Super::BeginPlay();
	
}

void AAREnemy::MoveToTarget(FVector TargetLocation)
{
}

// Called every frame
void AAREnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(enemyHealth <= 0)
	{
		Destroy(); // destroys enemy if its health is below zero 
	}

}

// Called to bind functionality to input
void AAREnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

