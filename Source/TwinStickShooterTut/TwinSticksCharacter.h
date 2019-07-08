// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/MeshComponent.h"
#include "Engine/EngineTypes.h"
#include "TwinSticksCharacter.generated.h"

class AGun;
class UAudioComponent;


// TODO: Tui zvuchi mnogo tupo. Rename na neshto po-umno
UCLASS(Blueprintable)
class TWINSTICKSHOOTERTUT_API ATwinSticksCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATwinSticksCharacter();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void TakeDamage(float Damage);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// TODO: Figure out how to make a blueprint getter.
	// losh kod ama ako ne e public ne bachka v animaciqta.
	UPROPERTY(BlueprintReadOnly)
	bool bDead;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Base Character")
	float Health;

	UPROPERTY(BlueprintReadWrite, Category = "Base Character")
	UMeshComponent* CharacterMesh;

	UPROPERTY(Instanced)
	UAudioComponent* DeathSoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character", Meta = (ClampMin = 0.01))
	float DeathAnimationTime;

	UPROPERTY(EditDefaultsOnly, Category = "Gun")
	TSubclassOf<AGun> StartingGunTemplate = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Gun")
	AGun* Gun = nullptr;
	
	UFUNCTION()
	virtual void Die();

	UFUNCTION()
	void LookInDirection(FVector Direction);

	UFUNCTION()
	void SpawnStartingGun();

	UFUNCTION()
	void AttachGun(AGun* NewGun);

	UFUNCTION()
	void StartFiring();

	UFUNCTION()
	void StopFiring();

	UFUNCTION()
	virtual void OnDeathTimerEnd();

private:
	FTimerHandle DeathTimerHandle;

	void MoveForward(float Value);

	void MoveRight(float Value);
};
