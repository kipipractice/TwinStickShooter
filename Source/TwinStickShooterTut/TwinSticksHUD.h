// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "TwinSticksHUD.generated.h"

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
	void SetScore(int Score);


	


protected:
	UPROPERTY(VisibleAnywhere, Category = "Health")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	UProgressBar* HealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	UTextBlock* ScoreText;


};
