// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "ShootingEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API AShootingEnemyAIController : public AEnemyAIController
{
	GENERATED_BODY()
public:

protected:
	void Tick(float DeltaTime) override;

	bool bFiring = false;

	bool CanSeeTarget();
};
