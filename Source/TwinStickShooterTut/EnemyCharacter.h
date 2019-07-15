// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwinSticksCharacter.h"
#include "EnemyCharacter.generated.h"

//forward declarations
class UBoxComponent;
class APlayerCharacter;

UCLASS()
class TWINSTICKSHOOTERTUT_API AEnemyCharacter : public ATwinSticksCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	void SetTarget(AActor* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Die() override;

	// Added score when enemy dies.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Score = 500.0f;

	// target player used for checking collision actor
	UPROPERTY()
	AActor* Target = nullptr;
};
