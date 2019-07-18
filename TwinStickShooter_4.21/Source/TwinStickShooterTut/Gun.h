// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USceneComponent;
class UAudioComponent;

UCLASS()
class TWINSTICKSHOOTERTUT_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	
	UFUNCTION()
	void PullTrigger();

	UFUNCTION()
	void ReleaseTrigger();

	UFUNCTION()
	float GetFireRate();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	USceneComponent* GunSpawnPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileTemplate;

	UPROPERTY(EditAnywhere, Instanced, Category = "Sound")
	UAudioComponent* FireSoundComponent;
	
	// Ammount of times gun can fire in a second.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun")
	float FireRate = 5;

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void SpawnProjectile();

	UFUNCTION()
	void PlayFireSound();

	FTimerHandle FireTimerHandle;
};