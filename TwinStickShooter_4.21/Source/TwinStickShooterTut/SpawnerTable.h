// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpawnerTable.generated.h"

class ATwinSticksCharacter;
class AEnemyCharacter;

USTRUCT(BlueprintType, Meta=(DisplayName="SpawnerInfo"))
struct FSpawnerInfo {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemyCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATwinSticksCharacter> EnemyAsset;
};



USTRUCT(BlueprintType)
struct FSpawnerTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FSpawnerTable()
		:
		SpawnerEnemyPlacement()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	TArray<struct FSpawnerInfo> SpawnerEnemyPlacement;
};
