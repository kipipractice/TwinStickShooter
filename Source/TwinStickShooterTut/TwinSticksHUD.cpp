// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSticksHUD.h"
#include "PlayerStatsWidget.h"


ATwinSticksHUD::ATwinSticksHUD() {
	PrimaryActorTick.bCanEverTick = false;
}


void ATwinSticksHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if (IsValid(PlayerStatsWidgetTemplate) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinSticksHUD::ATwinSticksHUD IsValid(PlayerStatsWidgetTemplate) == false"));
		return;
	}

	PlayerStatsWidget = Cast<UPlayerStatsWidget>(CreateWidget(GetWorld(), PlayerStatsWidgetTemplate));
	if (IsValid(PlayerStatsWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinSticksHUD::ATwinSticksHUD IsValid(PlayerStatsWidget) == false"));
		return;
	}
	PlayerStatsWidget->AddToViewport();
}


UPlayerStatsWidget* ATwinSticksHUD::GetPlayerStatsWidget() {
	if (IsValid(PlayerStatsWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinSticksHUD::GetPlayerStatsWidget IsValid(PlayerStatsWidget) == false"));
	}
	return PlayerStatsWidget;
}