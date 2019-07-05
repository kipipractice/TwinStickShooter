// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USceneComponent;

UCLASS()
class TWINSTICKSHOOTERTUT_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Projectile)
	void Fire();

	float GetFireRate();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	USceneComponent* GunSpawnPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileTemplate;

	// Ammount of times gun can fire in a second.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gun)
	float FireRate = 5;
};