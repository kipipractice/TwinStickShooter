// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwinSticksCharacter.h"
#include "PlayerCharacter.generated.h"




enum class InputType : uint8;

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API APlayerCharacter : public ATwinSticksCharacter
{
	DECLARE_DYNAMIC_DELEGATE(FLookAroundDelegate);

	GENERATED_BODY()


public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;


	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	InputType ControllerInputType;

	// Only register controller input if vector length is above this value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	float InputDeadZone = 0.5f;

	UFUNCTION()
	void LookAtMousePosition();

	UFUNCTION()
	void LookAtInputAxisDirection();

	FLookAroundDelegate LookAroundDelegate;
	
};
