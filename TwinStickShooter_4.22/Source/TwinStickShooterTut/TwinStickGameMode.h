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
class ACharacterPlayerController;

/**
 * 
 */

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
	UFUNCTION()
	virtual void RespawnPlayer();

	UFUNCTION()
	void IncrementEnemyCounter(int EnemyCount);

	UFUNCTION()
	virtual void DecrementEnemyCounter();

	void SetPlayerRespawnLocation(FTransform Location);

	UFUNCTION()
	void RestartLevel();

	UFUNCTION()
	void LoadWinLevel();

protected:

	UFUNCTION()
	virtual void WinGame();

	UFUNCTION()
	virtual void LoseGame();

	UFUNCTION()
	bool AreAllEnemiesDead();

	UFUNCTION()
	void UpdateHUDScore(int Score);

	void FindPlayerControllers();


	UPROPERTY(EditDefaultsOnly)
	FName WinGameLevel;

	UPROPERTY()
	FTransform PlayerRespawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class APlayerCharacter> PlayerTemplate;

	int CurrentScore = 0;

	int CurrentEnemies = 0;

	UPROPERTY()
	TArray<ACharacterPlayerController*> PlayerControllers;
};
