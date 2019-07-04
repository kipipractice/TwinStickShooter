// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwinStickGameMode.generated.h"


//forward declarations
class ATwinSticksCharacter;
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


	FSpawnEnemies OnSpawnEnemies;

protected:
	void SpawnEnemies();

	UPROPERTY(BlueprintReadOnly)
		int CurrentScore = 0;
	UPROPERTY(BlueprintReadWrite)
		float WaveTimeInterval = 1.0f;
	UPROPERTY(BlueprintReadWrite)
		FTransform PlayerRespawnLocation;
	// TODO: TSubclassOf<ATwinStickCharacter> and find a way to cast it to AActor
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> EnemyClass;
	//player class reference
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATwinSticksCharacter> PlayerClass;

	FTimerHandle SpawnTimerHandler;

};
