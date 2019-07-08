// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSticksHUD.h"
#include "Containers/UnrealString.h"
#include "DebugPrinter.h"

void ATwinSticksHUD::SetMaxHealth(float Health) {
	MaxHealth = Health;
}

void ATwinSticksHUD::SetHealth(float Health) {
	if (!ensure(HealthBar)) {
		DebugPrinter::Print("No healthbar!", EMessageType::Error);
		return;
	}

	HealthBar->SetPercent((float)(Health / MaxHealth));
}


void ATwinSticksHUD::SetScore(int Score) {

	if (!ensure(ScoreText)) {
		DebugPrinter::Print("No score text!", EMessageType::Error);
		return;
	}

	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}