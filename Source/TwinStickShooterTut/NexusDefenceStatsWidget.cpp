// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusDefenceStatsWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "TimerManager.h"
#include "NexusDefenceGameMode.h"
#include "Nexus.h"
#include "HealthComponent.h"


void UNexusDefenceStatsWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (IsValid(GameEndText) == false) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::UNexusDefenceStatsWidget IsValid(GameEndText) == false"));
		return;
	}
	GameEndText->SetVisibility(ESlateVisibility::Collapsed);
}


float UNexusDefenceStatsWidget::GetMaxNexusHealth() {
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::BeginPlay IsValid(World) == false"));
		return 0;
	}

	ANexusDefenceGameMode* NexusDefence = Cast<ANexusDefenceGameMode>(World->GetAuthGameMode());
	if (IsValid(NexusDefence) == false) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::BeginPlay IsValid(NexusDefence) == false"));
		return 0;
	}

	ANexus* Nexus = NexusDefence->GetNexus();
	if (IsValid(Nexus) == false) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::BeginPlay IsValid(Nexus) == false"));
		return 0;
	}

	UHealthComponent* HealthComponent = Nexus->FindComponentByClass<UHealthComponent>();
	if (IsValid(HealthComponent) == false) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::BeginPlay IsValid(HealthComponent) == false"));
		return 0;
	}
	return HealthComponent->GetMaxHealth();
}


void UNexusDefenceStatsWidget::SetLoseGame() {
	if (IsValid(GameEndText) == false) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::SetLoseGame IsValid(GameEndText) == false"));
		return;
	}
	if (LoseGameText.ToString() == FString("")) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::SetLoseGame LoseGameText.ToString() == FString("")"));
		return;
	}
	GameEndText->SetText(LoseGameText);
	GameEndText->SetColorAndOpacity(FSlateColor(FColor::Red));
	GameEndText->SetVisibility(ESlateVisibility::Visible);
}


void UNexusDefenceStatsWidget::SetWinGame() {
	if (IsValid(GameEndText) == false) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::SetWinGame IsValid(GameEndText) == false"));
		return;
	}
	if (WinGameText.ToString() == FString("")) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::SetWinGame WinGameText.ToString() == FString("")"));
		return;
	}
	GameEndText->SetText(WinGameText);
	GameEndText->SetColorAndOpacity(FSlateColor(FColor::Green));
	GameEndText->SetVisibility(ESlateVisibility::Visible);
}


void UNexusDefenceStatsWidget::SetNexusHealth(int Health) {
	if (IsValid(NexusHealthBar) == false) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::SetNexusHealth IsValid(NexusHealthBar) == false"));
		return;
	}
	float MaxNexusHealth = GetMaxNexusHealth();
	if (MaxNexusHealth == 0) {
		UE_LOG(LogTemp, Error, TEXT("UNexusDefenceStatsWidget::SetNexusHealth MaxNexusHealth == 0"));
		return;
	}
	NexusHealthBar->SetPercent((float)(Health / MaxNexusHealth));
}