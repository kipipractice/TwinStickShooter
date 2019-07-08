// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "InputType.h"
#include "DebugPrinter.h"

ACharacterPlayerController::ACharacterPlayerController() {
	USettingsSaveGame* LoadGameInstance = Cast<USettingsSaveGame>(
		UGameplayStatics::LoadGameFromSlot(SettingsSaveName, SaveSlotIndex)
	);

	if (LoadGameInstance) {
		ControllerDeviceInputType = LoadGameInstance->Type;

		if (ControllerDeviceInputType == InputType::Controller) {
			//UE_LOG(LogTemp, Warning, TEXT("Load Controller"));
			DebugPrinter::Print("Loading Controller settings", EMessageType::Info);
		}
		else if (ControllerDeviceInputType == InputType::PC)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Load PC"));
			DebugPrinter::Print("Loading PC settings", EMessageType::Info);
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Could not find device config! Loading default PC controls"));
		DebugPrinter::Print("Could not find device config! Loading default PC controlls instead");
		ControllerDeviceInputType = InputType::PC;
	}
}


void ACharacterPlayerController::BeginPlay() {
	Super::BeginPlay();
}


InputType ACharacterPlayerController::GetInputType() {
	if (ControllerDeviceInputType == InputType::Controller) {
		//UE_LOG(LogTemp, Warning, TEXT("Get Controller"));
		DebugPrinter::Print("Using controller settings");
	}
	else if (ControllerDeviceInputType == InputType::PC)
	{
		DebugPrinter::Print("Using PC settings");
		//UE_LOG(LogTemp, Warning, TEXT("Get PC"));
	}
	return ControllerDeviceInputType;
}