// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTarget.h"
#include "AREnemyCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyTarget::AEnemyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Bullet Collision")); //setup collision sphere for target
	CollisionSphere->InitSphereRadius(30.0f);

	RootComponent = CollisionSphere; //sets the root to the collision sphere
}

// Called when the game starts or when spawned
void AEnemyTarget::BeginPlay()
{
	Super::BeginPlay();
	auto Temp = GetWorld()->GetGameState(); //upon begin play get gamestate 
	Gamestate_ = Cast<ACustomGameState>(Temp);

	auto GetGM = GetWorld()->GetAuthGameMode();//upon begin play get gamemode
	Gamemode_ = Cast<ACustomGameMode>(GetGM);
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,&AEnemyTarget::onhit); 
}

// Called every frame
void AEnemyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyTarget::onhit(UPrimitiveComponent* HitComp, AActor* actor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AAREnemyCharacter* Enemy = Cast<AAREnemyCharacter>(actor); //cast enemy object to the actor we are checking is hit

	if(IsValid(Enemy))//checks if collision is enemy
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Player Lost life"));
			GWorld->DestroyActor(Enemy); //destroys the enemy
			if(IsValid(Gamestate_))//check game state pointer is valid 
			{
				Gamestate_->PlayerHealth -= 25.0f; //takes 25 away from health
				if(IsValid(Gamemode_))
				{
					Gamemode_->CheckPlayerHealth();//checks if player health is less than zero, to transition to lose state
				}
			}
			
		}
}



