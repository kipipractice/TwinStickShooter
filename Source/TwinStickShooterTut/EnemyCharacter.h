// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwinSticksCharacter.h"
#include "EnemyCharacter.generated.h"

//forward declarations
class UBoxComponent;
class APlayerCharacter;

UCLASS()
class TWINSTICKSHOOTERTUT_API AEnemyCharacter : public ATwinSticksCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	void SetTarget(AActor* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Die() override;

	//Box component overlap begin overlap event
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	//Box component overlap end overlap event
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void DealDamage();

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* DamageBox = nullptr;

	//Rate at which the ai controller deals damage (in seconds)
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DamageRate = 1.0f;

	//Delay before starting to deal damage (in seconds)
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DamageDelay = 0.1f;

	//Damage to deal to the player, per hit
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DamagePerHit = 30.0f;

	// Added score when enemy dies.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Score = 500.0f;


	FTimerHandle DamageTimerHandle;

	// target player used for checking collision actor
	UPROPERTY()
	AActor* Target = nullptr;
};
