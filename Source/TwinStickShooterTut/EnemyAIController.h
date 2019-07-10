// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class APlayerCharacter;
class AEnemyCharacter;
class ANexus;
/**
 * 
 */

UENUM()
enum class EFollowActorType : uint8 {
	Player,
	Nexus
};


UCLASS()
class TWINSTICKSHOOTERTUT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	AEnemyAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Tick(float DeltaTime) override;

	void OnPossess(APawn* PossessedPawn) override;

	FTimerHandle TrackPlayerTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	EFollowActorType DefaultActorTypeToFollow;

	EFollowActorType CurrentlyTargetedActorType;

	UPROPERTY()
	AActor* TargetToFollow = nullptr;

	UPROPERTY()
	AEnemyCharacter* ControlledEnemy;

	// interval at which the enemy changes direction and moves towards the player(in seconds)
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TrackInterval = 0.25f;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TrackDelay = 0.25f;

	// The distance to player at which enemy stops following nexus and starts following player.
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetPlayerDistance = 200;

	// Distance to nexus at which distance to player doesnt matter and enemy won't change its target.
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetNexusDistance = 200;

	void SwitchTarget(EFollowActorType ActorTypeToFollow);

	APlayerCharacter* GetPlayerCharacter();

	ANexus* GetNexus();

	void ResetFollowTarget();

	void DecideTarget();

	void LookAtTarget();
};