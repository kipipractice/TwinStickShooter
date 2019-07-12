// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusDefenceStatsWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "TimerManager.h"
#include "NexusDefenceGameMode.h"
#include "Nexus.h"
#include "HealthComponent.h"
#include "CustomMacros.h"


void UNexusDefenceStatsWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (validate(IsValid(GameEndText)) == false) { return; }

	GameEndText->SetVisibility(ESlateVisibility::Collapsed);
}


float UNexusDefenceStatsWidget::GetMaxNexusHealth() {
	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return 0; }

	ANexusDefenceGameMode* NexusDefence = Cast<ANexusDefenceGameMode>(World->GetAuthGameMode());
	if (validate(IsValid(NexusDefence)) == false) { return 0; }

	ANexus* Nexus = NexusDefence->GetNexus();
	if (validate(IsValid(Nexus)) == false) { return 0; }

	UHealthComponent* HealthComponent = Nexus->FindComponentByClass<UHealthComponent>();
	if (validate(IsValid(HealthComponent)) == false) { return 0; }

	return HealthComponent->GetMaxHealth();
}


void UNexusDefenceStatsWidget::SetLoseGame() {
	if (validate(IsValid(GameEndText)) == false) { return; }

	if (validate(LoseGameText.ToString() != FString(""))) {
		GameEndText->SetText(LoseGameText);
		GameEndText->SetColorAndOpacity(FSlateColor(FColor::Red));
		GameEndText->SetVisibility(ESlateVisibility::Visible);
	}
}


void UNexusDefenceStatsWidget::SetWinGame() {
	if (validate(IsValid(GameEndText)) == false) { return; }

	if (validate(WinGameText.ToString() != FString(""))) {
		GameEndText->SetText(WinGameText);
		GameEndText->SetColorAndOpacity(FSlateColor(FColor::Green));
		GameEndText->SetVisibility(ESlateVisibility::Visible);
	}
}


void UNexusDefenceStatsWidget::SetNexusHealth(int Health) {
	if (validate(IsValid(NexusHealthBar)) == false) { return; }

	float MaxNexusHealth = GetMaxNexusHealth();
	if (validate(MaxNexusHealth > 0)) {
		NexusHealthBar->SetPercent((float)(Health / MaxNexusHealth));
	}
}