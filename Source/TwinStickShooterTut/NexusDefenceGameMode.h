// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwinStickGameMode.h"
#include "NexusDefenceGameMode.generated.h"


class ANexus;
class UDataTable;
class UNexusDefenceStatsWidget;
/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API ANexusDefenceGameMode : public ATwinStickGameMode
{
	GENERATED_BODY()

public:
	ANexus* GetNexus();

protected:
	void BeginPlay() override;

	UPROPERTY()
	ANexus* Nexus = nullptr;

	UFUNCTION()
	void SetNexusHealth(int Health);

	void LoseGame() override;

	void WinGame() override;

	void DecrementEnemyCounter() override;

	//UPROPERTY(EditDefaultsOnly, Category = "Setup")
	//UDataTable* SpawnerLookupTable = nullptr;

	int CurrentWaveIndex = 0;

	UFUNCTION()
	void SpawnEnemyWave();

	UFUNCTION()
	void SpawnEnemyWaveOnNextFrame();

	void RespawnPlayer() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<int> EnemiesPerWave;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AEnemyCharacter> BossTemplate;

private:
	UNexusDefenceStatsWidget* GetNexusStatsWidget(APlayerController* PlayerController);
};
