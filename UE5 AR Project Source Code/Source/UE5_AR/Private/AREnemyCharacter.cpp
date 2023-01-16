// Fill out your copyright notice in the Description page of Project Settings.


#include "AREnemyCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAREnemyCharacter::AAREnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyDeathSFX = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("SoundCue'/Game/Assets/Audio/enemy_death_Cue.enemy_death_Cue'")).Object;
}

// Called when the game starts or when spawned
void AAREnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAREnemyCharacter::DamageReceived(float DamageTaken)
{
	EnemyHealth -= DamageTaken;// takes damage away from enemies health
	
	if(EnemyHealth <= 0.0f)
	{
		Destroy(); // destroys enemy if health reaches 0
		UGameplayStatics::PlaySoundAtLocation(this,EnemyDeathSFX,GetActorLocation(),GetActorRotation());
	}
}

// Called every frame
void AAREnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAREnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

}

