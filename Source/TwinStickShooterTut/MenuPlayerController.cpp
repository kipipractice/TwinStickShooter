// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerController.h"

AMenuPlayerController::AMenuPlayerController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	UE_LOG(LogTemp, Warning, TEXT("Should show mouse!"));
}