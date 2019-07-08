// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	AEnemyAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Tick(float DeltaTime);

	APlayerCharacter* PlayerToFollow = nullptr;

	FTimerHandle TrackPlayerTimerHandle;

	//interval at which the enemy changes direction and moves towards the player(in seconds)
	UPROPERTY(EditDefaultsOnly)
	float TrackInterval = 0.25f;

	UPROPERTY(EditDefaultsOnly)
	float TrackDelay = 0.25f;

	void FollowActor();
};
