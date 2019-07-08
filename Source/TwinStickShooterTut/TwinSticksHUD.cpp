// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSticksHUD.h"
#include "Containers/UnrealString.h"

void ATwinSticksHUD::SetMaxHealth(float Health) {
	MaxHealth = Health;
}

void ATwinSticksHUD::SetHealth(float Health) {
	if (IsValid(HealthBar) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinSticksHUD::SetScore IsValid(HealthBar) == false"));
		return;
	}

	HealthBar->SetPercent((float)(Health / MaxHealth));
}


void ATwinSticksHUD::SetScore(int Score) {
	if (IsValid(ScoreText) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinSticksHUD::SetScore IsValid(ScoreText) == false"));
		return;
	}

	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}