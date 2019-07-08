// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "InputType.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuHUD::SetInputType(InputType Type) {
	this->Type = Type;
}

void AMainMenuHUD::SaveSettings() {
	USettingsSaveGame* SaveGameInstance = Cast<USettingsSaveGame>(
		UGameplayStatics::CreateSaveGameObject(USettingsSaveGame::StaticClass())
	);

	if (IsValid(SaveGameInstance)) {
		SaveGameInstance->Type = Type;

		UGameplayStatics::SaveGameToSlot(
			SaveGameInstance,
			SaveGameInstance->GetSaveSlotName(),
			SaveGameInstance->GetUserIndex()
		);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainMenuHUD::SaveSettings() IsValid(SaveGameInstance) == false"));
	}
}