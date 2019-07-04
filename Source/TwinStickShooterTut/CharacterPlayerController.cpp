// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "InputType.h"


ACharacterPlayerController::ACharacterPlayerController() {
	USettingsSaveGame* LoadGameInstance = Cast<USettingsSaveGame>(
		UGameplayStatics::LoadGameFromSlot(SettingsSaveName, SaveSlotIndex)
	);

	if (LoadGameInstance) {
		ControllerDeviceInputType = LoadGameInstance->Type;

		if (ControllerDeviceInputType == InputType::Controller) {
			UE_LOG(LogTemp, Warning, TEXT("Load Controller"));
		}
		else if (ControllerDeviceInputType == InputType::PC)
		{
			UE_LOG(LogTemp, Warning, TEXT("Load PC"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find device config! Loading default PC controls"));
		ControllerDeviceInputType = InputType::PC;
	}
}


void ACharacterPlayerController::BeginPlay() {
	Super::BeginPlay();
}


InputType ACharacterPlayerController::GetInputType() {
	if (ControllerDeviceInputType == InputType::Controller) {
		UE_LOG(LogTemp, Warning, TEXT("Get Controller"));
	}
	else if (ControllerDeviceInputType == InputType::PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get PC"));
	}
	return ControllerDeviceInputType;
}