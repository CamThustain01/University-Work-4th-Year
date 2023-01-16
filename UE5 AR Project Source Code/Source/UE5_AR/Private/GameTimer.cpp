// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTimer.h"

// Sets default values
AGameTimer::AGameTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimeRemainingText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Time Remaining"));
	TimeRemainingText->SetHorizontalAlignment(EHTA_Right);
	TimeRemainingText->SetWorldSize(100.0f);
	RootComponent = TimeRemainingText;
	TimeRemaining = 120; //player has 2 minutes to survive

}

// Called when the game starts or when spawned
void AGameTimer::BeginPlay()
{
	Super::BeginPlay();

	UpdateTimer();
	GetWorldTimerManager().SetTimer(Ticker, this, &AGameTimer::BeginTimer,1.0f,true);
	
}

void AGameTimer::UpdateTimer()
{
	//TimeRemainingText->SetText(FString::FromInt(FMath::Max(TimeRemaining,0)));
	//TimeRemainingText->SetText(FString::FromInt(FMath::Max(TimeRemaining, 0)));
	
}

void AGameTimer::BeginTimer()
{
	UpdateTimer();
	if(TimeRemaining < 1)
	{
		GetWorldTimerManager().ClearTimer(Ticker);
		CheckTimer();
		
	}
}

void AGameTimer::CheckTimer()
{
	//TimeRemainingText->SetText(TEXT("You Survived"));

	//change widget to you win widget.......
}

// Called every frame
void AGameTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

