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
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Warning, TEXT("AEnemyCharacter::BeginPlay IsValid(World) == false"))
		return;
	}
	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (IsValid(FirstPlayerController) == false) {
		UE_LOG(LogTemp, Warning, TEXT("AEnemyCharacter::BeginPlay IsValid(FirstPlayerController) == false"))
		return;

	}
	PlayerCharacter = Cast<APlayerCharacter>(FirstPlayerController->GetPawn());
	if (IsValid(PlayerCharacter) == false) {
		UE_LOG(LogTemp, Warning, TEXT("AEnemyCharacter::BeginPlay IsValid(PlayerCharacter) == false"))
	}
}


void AEnemyCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(PlayerCharacter) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::OnBoxBeginOverlap IsValid(PlayerCharacter) == false"));
		return;
	}

	if (OtherActor == PlayerCharacter) {
		GetWorldTimerManager().SetTimer(
			DamageTimerHandle,
			this,
			&AEnemyCharacter::DealDamage,
			DamageRate,
			true,
			DamageDelay);
	}

}

void AEnemyCharacter::DealDamage()
{
	if (IsValid(PlayerCharacter) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::DealDamage IsValid(PlayerCharacter) == false"));
		return;
	}

	UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
	if (IsValid(HealthComponent)) {
		HealthComponent->TakeDamage(DamagePerHit);
	}
}

void AEnemyCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(PlayerCharacter) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyCharacter::OnOverlapEnd IsValid(PlayerCharacter) == false"));
		return;
	}

	if (OtherActor == PlayerCharacter) {
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
