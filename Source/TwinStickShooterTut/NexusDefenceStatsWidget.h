// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NexusDefenceStatsWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API UNexusDefenceStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetLoseGame();

	void SetWinGame();

	void SetNexusHealth(int Health);

protected:
	void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UProgressBar* NexusHealthBar;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UTextBlock* GameEndText;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FText WinGameText;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FText LoseGameText;
	// Get nexus max health by getting it directly from nexus.
	float GetMaxNexusHealth();
};
