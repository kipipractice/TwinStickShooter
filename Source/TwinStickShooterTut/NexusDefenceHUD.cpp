// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusDefenceHUD.h"
#include "NexusDefenceStatsWidget.h"

UNexusDefenceStatsWidget* ANexusDefenceHUD::GetNexusDefenceWidget() {
	return NexusDefenceWidget;
}

void ANexusDefenceHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if (IsValid(NexusDefenceWidgetTemplate) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceHUD::PostInitializeComponents IsValid(PlayerStatsWidgetTemplate) == false"));
		return;
	}

	NexusDefenceWidget = Cast<UNexusDefenceStatsWidget>(CreateWidget(GetWorld(), NexusDefenceWidgetTemplate));
	if (IsValid(NexusDefenceWidgetTemplate) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceHUD::PostInitializeComponents IsValid(NexusDefenceWidgetTemplate) == false"));
		return;
	}
	NexusDefenceWidget->AddToViewport();
}