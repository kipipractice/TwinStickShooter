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

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	EFollowActorType DefaultActorTypeToFollow;

	EFollowActorType CurrentlyTargetedActorType;

	UPROPERTY()
	AActor* Target = nullptr;

	UPROPERTY()
	AEnemyCharacter* ControlledEnemy;


	// The distance to player at which enemy stops following nexus and starts following player.
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetPlayerDistance = 200.0f;

	// Distance to nexus at which distance to player doesnt matter and enemy won't change its target.
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetNexusDistance = 200.0f;

	bool bLockedToNexus = false;

	void SwitchTarget(EFollowActorType ActorTypeToFollow);

	APlayerCharacter* GetPlayerCharacter();

	ANexus* GetNexus();

	void FollowTarget();

	void DecideTarget();

	void LookAtTarget();
};