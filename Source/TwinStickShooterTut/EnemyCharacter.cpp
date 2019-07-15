// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "TwinStickGameMode.h"
#include "CustomMacros.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

}


void AEnemyCharacter::SetTarget(AActor* Target) {
	if (validate(IsValid(Target)) == false) { return; }

	this->Target = Target;
}


void AEnemyCharacter::Die() {
	Super::Die();

	AController* Controller = GetController();
	if (validate(IsValid(Controller)) == false) { return; }

	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(World->GetAuthGameMode());
	if (validate(IsValid(GameMode)) == false) { return; }

	Controller->StopMovement();
	Controller->Destroy();
	SetActorEnableCollision(false);
	GameMode->IncrementScore(Score);
}


void AEnemyCharacter::Destroyed() {
	Super::Destroyed();

	UE_LOG(LogTemp, Warning, TEXT("DEstroyed!"));

	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(World->GetAuthGameMode());
	if (validate(IsValid(GameMode)) == false) { return; }

	GameMode->DecrementEnemyCounter();
}