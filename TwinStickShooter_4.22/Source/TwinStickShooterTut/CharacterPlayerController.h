// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterPlayerController.generated.h"

enum class InputType : uint8;
/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API ACharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterPlayerController();

	InputType GetInputType();

protected:

	InputType ControllerDeviceInputType;
	
};
