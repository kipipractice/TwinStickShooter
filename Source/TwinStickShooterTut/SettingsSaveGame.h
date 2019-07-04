// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSaveGame.generated.h"


enum class InputType : uint8;

const FString SettingsSaveName = "Settings";
const uint8 SaveSlotIndex = 0;

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API USettingsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	USettingsSaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
	InputType Type;

	FString GetSaveSlotName();

	uint32 GetUserIndex();

protected:
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
};
