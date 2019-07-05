// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSticksHUD.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "DebugPrinter.h"



void ATwinSticksHUD::SetMaxHealth(float Health) {
	MaxHealth = Health;
}

void ATwinSticksHUD::SetHealth(float Health) {
	/*
	if (!HealthBar) {
		DebugPrinter::Print("No healthbar!");
	}

	HealthBar->SetPercent((float)(Health / MaxHealth));
	*/
}


void ATwinSticksHUD::SetScore(float Score) {
	/*
	if (!ScoreText) {
		DebugPrinter::Print("No score text!");
	}

	ScoreText->SetText(FText::AsPercent(Score));
	*/
}