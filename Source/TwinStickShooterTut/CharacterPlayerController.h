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

	ACharacterPlayerController();


public:
	InputType GetInputType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	InputType ControllerDeviceInputType;
	
};
