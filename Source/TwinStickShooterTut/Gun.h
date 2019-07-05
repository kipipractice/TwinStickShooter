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


	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void PullTrigger();

	// start spawning projectiles at the specified gun spawn position
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void ReleaseTrigger();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Fire();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	USceneComponent* ProjectileSpawnPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileTemplate;

	// Amount of times gun can fire in a second.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
	float FireRate = 10.0f;

	FTimerHandle FireTimerHandle;

	UAudioComponent* AudioComponent;

};