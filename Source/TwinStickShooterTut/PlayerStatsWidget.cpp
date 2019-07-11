// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Containers/UnrealString.h"


void UPlayerStatsWidget::SetMaxHealth(float Health) {
	MaxHealth = Health;
}

void UPlayerStatsWidget::SetHealth(float Health) {
	if (IsValid(HealthBar) == false) {
		UE_LOG(LogTemp, Error, TEXT("UPlayerStatsWidget::SetScore IsValid(HealthBar) == false"));
		return;
	}

	HealthBar->SetPercent((float)(Health / MaxHealth));
}


void UPlayerStatsWidget::SetScore(int Score) {
	if (IsValid(ScoreText) == false) {
		UE_LOG(LogTemp, Error, TEXT("UPlayerStatsWidget::SetScore IsValid(ScoreText) == false"));
		return;
	}

	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}