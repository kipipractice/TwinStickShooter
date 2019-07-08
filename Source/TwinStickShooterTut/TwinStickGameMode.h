// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwinStickGameMode.generated.h"


//forward declarations
class AEnemyCharacter;
class APlayerCharacter;

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnEnemies);

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

	void SetPlayerRespawnLocation(FTransform PlayerRespawnTransform);

	FSpawnEnemies OnSpawnEnemies;

protected:
	void SpawnEnemies();

	int CurrentScore = 0;

	UPROPERTY(EditDefaultsOnly)
	float WaveTimeInterval = 1.0f;
	
	UPROPERTY(EditDefaultsOnly)
	FTransform PlayerRespawnLocation;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyCharacter> EnemyClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerCharacter> PlayerClass;

	FTimerHandle SpawnTimerHandler;

	UFUNCTION()
	void UpdateHUDScore(int Score);

};
