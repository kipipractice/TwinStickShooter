// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"


class UMainMenuWidget;
class USettingsWidget;

enum class InputType : uint8;

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	void LoadMainMenu();

	void LoadSettingsMenu();

	UFUNCTION(BlueprintCallable)
	void SetInputType(InputType Type);

	UFUNCTION(BlueprintCallable)
	void SaveSettings();

	InputType Type;

protected:

	void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USettingsWidget> SettingsWidgetTemplate;

	UMainMenuWidget* MainMenuWidget;

	USettingsWidget* SettingsWidget;
};