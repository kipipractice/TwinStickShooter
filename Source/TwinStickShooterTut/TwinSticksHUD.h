// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TwinSticksHUD.generated.h"

class UPlayerStatsWidget;
/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API ATwinSticksHUD : public AHUD
{
	GENERATED_BODY()

	ATwinSticksHUD();

public:
	UFUNCTION()
	UPlayerStatsWidget* GetPlayerStatsWidget();

protected:
	void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> PlayerStatsWidgetTemplate;

	UPlayerStatsWidget* PlayerStatsWidget;
};
