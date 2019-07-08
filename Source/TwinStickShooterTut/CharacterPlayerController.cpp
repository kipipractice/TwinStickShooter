// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "InputType.h"


ACharacterPlayerController::ACharacterPlayerController() {
	USettingsSaveGame* LoadGameInstance = Cast<USettingsSaveGame>(
		UGameplayStatics::LoadGameFromSlot(SettingsSaveName, SaveSlotIndex)
	);

	if (IsValid(LoadGameInstance)) {
		ControllerDeviceInputType = LoadGameInstance->Type;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find device config! Loading default PC controlls instead!"));
		ControllerDeviceInputType = InputType::PC;
	}
}


InputType ACharacterPlayerController::GetInputType() {
	return ControllerDeviceInputType;
}