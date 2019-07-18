// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"


class UButton;
class USettingsWidget;

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()


protected:

	void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	FName FirstLevelName;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UButton* StartGameButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UButton* SettingsButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UButton* QuitButton;

	UFUNCTION()
	void StartLevel();

	UFUNCTION()
	void LoadSettingsMenu();

	UFUNCTION()
	void QuitGame();
};
