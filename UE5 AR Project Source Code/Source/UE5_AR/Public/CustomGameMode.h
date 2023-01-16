// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "HelloARManager.h"
#include "CustomGameState.h"
#include "CustomGameMode.generated.h"

//Forward Declarations
class APlaceableActor;
class AReloadActor;
class APowerupActor;

/**
 * 
 */

UCLASS()
class UE5_AR_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	//creates instances of different classes
	FTimerHandle Ticker;
	APlaceableActor* SpawnedActor;
	AReloadActor* ReloadActor;
	APowerupActor* PowerupActor;
	AHelloARManager* arManager;
	ACustomGameState* Gamestate_;

public:
	ACustomGameMode();
	virtual ~ACustomGameMode() = default;


	virtual void StartPlay() override;
	//function for starting game countdown
	void StartCountdown();
	//function for setting up the timer
	void LevelCountdown();

	//function for checking the health
	void CheckPlayerHealth();

	/**
	 * @brief An example of an event as generally seen within the Event Graph of Blueprints
	 *  You can have different implementations of this event which will be called when you call this as a delegate.
	 *	See the CPP For more information on the implementation
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "GameModeBase", DisplayName = "Start Play")
		void StartPlayEvent();



	/**
	 * @brief A Dummy event for spawning ACustomActor.
	 */
	/*UFUNCTION(BlueprintCallable, Category="Spawn")
		virtual void SpawnCube();*/
	
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * @brief Perform a line trace at the screen position provided and place a default Placeable actor on it.
	 * Create another actor class that inherits from APlaceableActor and is spawned here instead of the default one. Make sure this new object is placed on the Plane rather than halfway through a plane
	 * @param ScreenPos Pass the Screen Position as an FVector
	 */
	virtual void LineTraceSpawnActor(FVector ScreenPos);
	

	/**
	 * @brief This function is virtual - you can inherit this class to override this function
	 * Each level can have their own unique spawned actors but with similar base qualities using inheritance
	 */
	virtual void SpawnInitialActors();

	void LevelBegunSetup();//function which stops all plane tracking from the ar manager when called.

	//creates uproperty of placeable actor class so the level actor can be chosen in bp editor
	 UPROPERTY(Category="Placeable",EditAnywhere,BlueprintReadWrite)
	 TSubclassOf<APlaceableActor> PlacableToSpawn;
	//creates uproperty of reload actor class so the reload actor can be chosen in bp editor
	UPROPERTY(Category="Reload",EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AReloadActor> ReloadActorToSpawn;
	//creates uproperty of powerup actor class so the powerup actor can be chosen in bp editor
	UPROPERTY(Category="Reload",EditAnywhere,BlueprintReadWrite)
	TSubclassOf<APowerupActor> PowerupActorToSpawn;

	//variable for minutes 
	UPROPERTY(BlueprintReadOnly)
	int MinutesRemaining = 1; 
	//varibale for game seconds
	UPROPERTY(BlueprintReadOnly)
	int SecondsRemaining = 0;

	//booleans for level won and level lose
	UPROPERTY(BlueprintReadOnly)
	bool bLevelWon = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLevelLost = false;

};
