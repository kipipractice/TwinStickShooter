// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSticksHUD.h"
#include "PlayerStatsWidget.h"
#include "CustomMacros.h"

void ATwinSticksHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if (validate(IsValid(PlayerStatsWidgetTemplate)) == false) { return; }

	PlayerStatsWidget = Cast<UPlayerStatsWidget>(CreateWidget(GetWorld(), PlayerStatsWidgetTemplate));
	if (validate(IsValid(PlayerStatsWidget))) { 
		PlayerStatsWidget->AddToViewport();
	}
}


UPlayerStatsWidget* ATwinSticksHUD::GetPlayerStatsWidget() {
	if (validate(IsValid(PlayerStatsWidget)) == false) { return nullptr;  }

	return PlayerStatsWidget;
}