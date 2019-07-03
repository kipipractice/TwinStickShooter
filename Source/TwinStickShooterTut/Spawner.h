// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Spawner.generated.h"

class ATwinSticksCharacter;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Spawner)
	TSubclassOf<ATwinSticksCharacter> CharacterTemplate;

	void SpawnEnemy();

public:

	virtual void Tick(float DeltaTime) override;
};
