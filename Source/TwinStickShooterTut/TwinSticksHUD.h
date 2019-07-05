// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TwinSticksHUD.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API ATwinSticksHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetMaxHealth(float Health);

	UFUNCTION()
	void SetHealth(float Health);

	UFUNCTION()
	void SetScore(float Score);

protected:

	//UPROPERTY(BlueprintReadWrite)
	//UProgressBar* HealthBar;

	//UPROPERTY(BlueprintReadWrite)
	//UTextBlock* ScoreText;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float MaxHealth = 100;
};
