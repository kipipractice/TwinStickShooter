// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwinStickGameMode.generated.h"


//forward declarations
class AEnemyCharacter;
class APlayerCharacter;
class ATriggerVolume;
class ASpawner;
class UBoxComponent;

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnEnemies, int, WaveIndex);

UCLASS()
class TWINSTICKSHOOTERTUT_API ATwinStickGameMode : public AGameModeBase
{

	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	// Increments the score by a given amount
	UFUNCTION(BlueprintCallable)
	void IncrementScore(const int Amount);

	// Respawns the player to his initial transform
	UFUNCTION(BlueprintCallable)
	void RespawnPlayer();

	UFUNCTION()
	void IncrementEnemyCounter(int EnemyCount);

	UFUNCTION()
	void DecrementEnemyCounter();

	FSpawnEnemies OnSpawnEnemies;

	void SetPlayerRespawnLocation(FTransform Location);

protected:

	UFUNCTION()
	bool AreAllEnemiesDead();

	UFUNCTION()
	void UpdateHUDScore(int Score);

	void SpawnEnemyWave();

	void SpawnEnemyWaveOnNextFrame();

	UPROPERTY()
	FTransform PlayerRespawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class APlayerCharacter> PlayerTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AEnemyCharacter> EnemyClass;

	int CurrentScore = 0;

	int CurrentWaveIndex = 0;

	int CurrentEnemies = 0;

};
