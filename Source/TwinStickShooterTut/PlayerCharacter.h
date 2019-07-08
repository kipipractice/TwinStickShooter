// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwinSticksCharacter.h"
#include "PlayerCharacter.generated.h"

class ATwinSticksHUD;


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

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void TakeDamage(float Damage) override;

	void PossessedBy(AController* Controller) override;

protected:
	void BeginPlay() override;
	
	void Die() override;

	void OnDeathTimerEnd() override;

	FLookAroundDelegate LookAroundDelegate;

	UPROPERTY()
	ATwinSticksHUD* HUD;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	InputType ControllerInputType;

	// Only register controller input if vector length is above this value
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float InputDeadZone = 0.5f;

	UFUNCTION()
	void LookAtMousePosition();

	UFUNCTION()
	void LookAtInputAxisDirection();

	UFUNCTION()
	void SetMouseEventsEnabled(bool bEnabled);

	UFUNCTION()
	void SetupMouseInputScheme(UInputComponent* PlayerInputComponent);

	UFUNCTION()
	void SetupControllerInputScheme(UInputComponent* PlayerInputComponent);
};