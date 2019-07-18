// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "InputType.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "CustomMacros.h"
#include "SettingsWidget.h"
#include "MainMenuWidget.h"


void AMainMenuHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();

	LoadMainMenu();
}


void AMainMenuHUD::SetInputType(InputType Type) {
	this->Type = Type;
}

void AMainMenuHUD::SaveSettings() {
	USettingsSaveGame* SaveGameInstance = Cast<USettingsSaveGame>(
		UGameplayStatics::CreateSaveGameObject(USettingsSaveGame::StaticClass())
	);

	// Dont't use validate. Expected behaviour!
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
		UE_LOG(LogTemp, Warning, TEXT("AMainMenuHUD::SaveSettings IsValid(SaveGameInstance) == false"));
	}
}


void AMainMenuHUD::LoadSettingsMenu() {
	if (validate(IsValid(SettingsWidgetTemplate)) == false) { return; }

	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	SettingsWidget = Cast<USettingsWidget>(CreateWidget(World, SettingsWidgetTemplate));
	if (validate(IsValid(SettingsWidget)) == false) { return; }

	SettingsWidget->AddToViewport();

	if (IsValid(MainMenuWidget)) {
		MainMenuWidget->RemoveFromViewport();
	}
}


void AMainMenuHUD::LoadMainMenu() {
	UE_LOG(LogTemp, Warning, TEXT("AMainMenuHUD::LoadMainMenu"));

	if (validate(IsValid(MainMenuWidgetTemplate)) == false) { return; }

	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	MainMenuWidget = Cast<UMainMenuWidget>(CreateWidget(World, MainMenuWidgetTemplate));
	if (validate(IsValid(MainMenuWidget)) == false) { return; }

	if (IsValid(SettingsWidget)) {
		SettingsWidget->RemoveFromViewport();
	}

	MainMenuWidget->AddToViewport();
}