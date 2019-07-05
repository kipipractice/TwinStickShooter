// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/MeshComponent.h"
#include "Engine/EngineTypes.h"
#include "TwinSticksCharacter.generated.h"

class AGun;

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

	virtual void Die_Implementation();

	void LookInDirection(FVector Direction);

	void SetGun(AGun* NewGun);

	void StartFiring();

	void FireGun();

	void StopFiring();

private:
	FTimerHandle FireTimerHandle;

	void MoveForward(float Value);

	void MoveRight(float Value);
};
