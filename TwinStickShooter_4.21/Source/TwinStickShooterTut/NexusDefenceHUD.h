// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwinSticksHUD.h"
#include "NexusDefenceHUD.generated.h"

class UNexusDefenceStatsWidget;

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API ANexusDefenceHUD : public ATwinSticksHUD
{
	GENERATED_BODY()

public:
	UFUNCTION()
	UNexusDefenceStatsWidget* GetNexusDefenceWidget();

protected:
	void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UNexusDefenceStatsWidget> NexusDefenceWidgetTemplate;

	UNexusDefenceStatsWidget* NexusDefenceWidget;
};
