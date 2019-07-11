// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Spawner.generated.h"


//forward declarations
class AEnemyCharacter;
class UBoxComponent;
class UDataTable;
UCLASS()
class TWINSTICKSHOOTERTUT_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	void SpawnEnemyWave(int WaveIndex);

	void SpawnEnemy(TSubclassOf<AEnemyCharacter> EnemyTemplate);

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AEnemyCharacter> EnemyTemplate;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AEnemyCharacter> BossTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UDataTable* SpawnerLookupTable = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TArray<int> EnemiesPerWave;

};