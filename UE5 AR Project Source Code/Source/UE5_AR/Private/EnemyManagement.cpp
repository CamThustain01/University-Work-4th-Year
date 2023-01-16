// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagement.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyManagement::AEnemyManagement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyManagement::SpawnEnemy()
{

	auto Player = Cast<ACustomARPawn>(UGameplayStatics::GetPlayerPawn(this,0));
	if(IsValid(Player))
	{
		if(Player->getLevelState() == true) //if the level begun is true...
		{
			//spawn enemies .
			const FActorSpawnParameters SpawnInfo;
			const FRotator Rotation(0, 0, 0);
			const FVector Location(GetActorLocation().X,GetActorLocation().Y -45,GetActorLocation().Z +20);
			Enemy_ = GetWorld()->SpawnActor<AAREnemyCharacter>(PickEnemy,Location,Rotation,SpawnInfo); //spawns one enemy
		}
	}
	
	
}

void AEnemyManagement::SpawnEndless()
{
	
	//spawns enemies every four seconds
	float SpawnRate = FMath::RandRange(1,3);//produces a random number between 1,3 enemies will have different spawn rates
	GetWorldTimerManager().SetTimer(Ticker, this, &AEnemyManagement::SpawnEnemy, SpawnRate, true); //spawns enemy every 1-3 seconds based on location of spawner
		
	
}



// Called when the game starts or when spawned
void AEnemyManagement::BeginPlay()
{
	Super::BeginPlay();

	SpawnEndless();//should spawn endless enemies upon begin play
	
}

// Called every frame
void AEnemyManagement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



