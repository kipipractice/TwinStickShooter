// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"


enum class InputType : uint8;

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetInputType(InputType Type);

	UFUNCTION(BlueprintCallable)
	void SaveSettings();

	InputType Type;

};