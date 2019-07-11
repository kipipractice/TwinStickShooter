// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpawnerTable.generated.h"


class AEnemyCharacter;

USTRUCT(BlueprintType)
struct FSpawnerTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FSpawnerTable()
		: EnemyCount(0)
		, EnemyAsset(0)
	{}

	/** The 'Name' column is the same as the Current Wave */

	// Number of enemies to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	int EnemyCount;


	/** Enemy Asset*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		TAssetPtr<AEnemyCharacter> EnemyAsset;
};
