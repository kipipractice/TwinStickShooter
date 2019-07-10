// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Classes/AIController.h"
#include "GameFramework/Controller.h"

#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "TwinStickGameMode.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	if (IsValid(DamageBox) == false) {
		UE_LOG(LogTemp, Warning, TEXT("AEnemyCharacter::BeginPlay IsValid(DamageBox) == false"))
	}
	else 
	{
		DamageBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnBoxBeginOverlap);
		DamageBox->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapEnd);
	}
}


void AEnemyCharacter::SetTarget(AActor* Target) {
	if (IsValid(Target) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::SetTarget IsValid(Target) == false"));
		return;
	}
	this->Target = Target;
}


void AEnemyCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(Target) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::OnBoxBeginOverlap IsValid(Target) == false"));
		return;
	}

	if (OtherActor == Target) {
		GetWorldTimerManager().SetTimer(
			DamageTimerHandle,
			this,
			&AEnemyCharacter::DealDamage,
			DamageRate,
			true,
			DamageDelay
		);
	}

}

void AEnemyCharacter::DealDamage()
{
	if (IsValid(Target) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::DealDamage IsValid(Target) == false"));
		return;
	}

	UHealthComponent* HealthComponent = Target->FindComponentByClass<UHealthComponent>();
	if (IsValid(HealthComponent)) {
		HealthComponent->TakeDamage(DamagePerHit);
	}
}

void AEnemyCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(Target) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::OnOverlapEnd IsValid(Target) == false"));
		return;
	}

	if (OtherActor == Target) {
		GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	}
}


void AEnemyCharacter::Die() {
	Super::Die();

	AController* Controller = GetController();
	if (IsValid(Controller) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::Die IsValid(Controller) == false"))
		return;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::Die IsValid(World) == false"))
		return;
	}
	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(World->GetAuthGameMode());
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::Die IsValid(GameMode) == false"))
		return;
	}

	Controller->StopMovement();
	Controller->Destroy();
	SetActorEnableCollision(false);
	GameMode->IncrementScore(Score);
}
