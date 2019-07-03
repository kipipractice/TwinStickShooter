// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TwinSticksCharacter.generated.h"

class AGun;

UCLASS(Blueprintable)
class TWINSTICKSHOOTERTUT_API ATwinSticksCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATwinSticksCharacter();

	bool IsDead();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void TakeDamage(float Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Character")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Character")
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Character")
	bool bDead = false;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	AGun* Gun = nullptr;
	*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
private:
	void FireGun();
	*/
};
