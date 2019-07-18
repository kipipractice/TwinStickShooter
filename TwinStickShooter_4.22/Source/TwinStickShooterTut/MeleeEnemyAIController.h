// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "MeleeEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API AMeleeEnemyAIController : public AEnemyAIController
{
	GENERATED_BODY()
public:

protected:
	void BeginPlay() override;


	// interval at which the enemy changes direction and moves towards the player(in seconds)
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TrackInterval = 0.25f;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TrackDelay = 0.25f;

	FTimerHandle TrackPlayerTimerHandle;
};
