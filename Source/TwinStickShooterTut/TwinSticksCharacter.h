// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/MeshComponent.h"
#include "Engine/EngineTypes.h"
#include "TwinSticksCharacter.generated.h"

class AGun;
class UAudioComponent;

UCLASS(Blueprintable)
class TWINSTICKSHOOTERTUT_API ATwinSticksCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATwinSticksCharacter();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void TakeDamage(float Damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Base Character")
	void Die();

	// TODO: Figure out how to make a blueprint getter.
	UPROPERTY(BlueprintReadOnly)
	bool bDead;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Base Character")
	UMeshComponent* CharacterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Character")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Character")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun")
	TSubclassOf<AGun> StartingGunTemplate;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gun")
	AGun* Gun = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Sound")
	UAudioComponent* DeathSoundComponent;

	// Time for death animation to play. OnDeathTimerEnd() is called after that.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Base Character", Meta=(ClampMin = 0.01))
	float DeathAnimationTime;

	UFUNCTION()
	virtual void Die_Implementation();

	UFUNCTION()
	void LookInDirection(FVector Direction);

	UFUNCTION()
	void SetGun(AGun* NewGun);

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
