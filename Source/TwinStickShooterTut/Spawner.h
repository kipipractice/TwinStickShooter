// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Spawner.generated.h"


//forward declarations
class ATwinSticksCharacter;
class UBoxComponent;
class UDataTable;
UCLASS()
class TWINSTICKSHOOTERTUT_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();


	//Spawn specified number of enemies inside the box component
	UFUNCTION()
	void SpawnEnemy(TSubclassOf<ATwinSticksCharacter> EnemyTemplate, int Count);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	UBoxComponent* BoxComponent;

};