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

	// Sets the respawn location of the player, Call this funciton befre respawning the player
	UFUNCTION(BlueprintCallable)
		void SetPlayerRespawnLocation(const FTransform& Location);

	protected:
	UPROPERTY(BlueprintReadOnly)
		int CurrentScore;
	UPROPERTY(BlueprintReadWrite)
		float WaveTimeInterval;
	UPROPERTY(BlueprintReadWrite)
		FTransform PlayerRespawnLocation;
	// TODO: TSubclassOf<ATwinStickCharacter> and find a way to cast it to AActor
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> EnemyClass;
	//player class reference
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATwinSticksCharacter> PlayerClass;
};
