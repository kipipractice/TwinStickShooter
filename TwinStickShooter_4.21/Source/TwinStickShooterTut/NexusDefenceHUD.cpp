// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusDefenceHUD.h"
#include "NexusDefenceStatsWidget.h"
#include "CustomMacros.h"

UNexusDefenceStatsWidget* ANexusDefenceHUD::GetNexusDefenceWidget() {
	return NexusDefenceWidget;
}

void ANexusDefenceHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if (validate(IsValid(NexusDefenceWidgetTemplate)) == false) { return; }

	NexusDefenceWidget = Cast<UNexusDefenceStatsWidget>(CreateWidget(GetWorld(), NexusDefenceWidgetTemplate));
	if (validate(IsValid(NexusDefenceWidget)) == false) { return; }
	
	NexusDefenceWidget->AddToViewport();
}