// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpawnerTable.generated.h"


class ATwinSticksCharacter;

USTRUCT(BlueprintType)
struct FSpawnerTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FSpawnerTable()
		: SpawnerOneEnemyCount(0),
		SpawnerOneEnemyAsset(0),
		SpawnerTwoEnemyCount(0),
		SpawnerTwoEnemyAsset(0),
		SpawnerThreeEnemyCount(0),
		SpawnerThreeEnemyAsset(0)

	{}

	// "Name" is the same as the Wave Index

	// Number of enemies to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	int SpawnerOneEnemyCount;


	/** Enemy Asset*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	TSubclassOf<ATwinSticksCharacter> SpawnerOneEnemyAsset;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	int SpawnerTwoEnemyCount;

	/** Enemy Asset*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	TSubclassOf<ATwinSticksCharacter> SpawnerTwoEnemyAsset;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	int SpawnerThreeEnemyCount;


	/** Enemy Asset*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	TSubclassOf<ATwinSticksCharacter> SpawnerThreeEnemyAsset;
};
