// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "InputType.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuHUD::SetInputType(InputType Type) {
	UE_LOG(LogTemp, Warning, TEXT("Set Type to %d"), Type);
	this->Type = Type;
}

void AMainMenuHUD::SaveSettings() {
	USettingsSaveGame* SaveGameInstance = Cast<USettingsSaveGame>(
		UGameplayStatics::CreateSaveGameObject(USettingsSaveGame::StaticClass())
	);

	SaveGameInstance->Type = this->Type;
	UE_LOG(LogTemp, Warning, TEXT("Save type of %d"), this->Type);

	UGameplayStatics::SaveGameToSlot(
		SaveGameInstance,
		SaveGameInstance->GetSaveSlotName(),
		SaveGameInstance->GetUserIndex()
	);
}