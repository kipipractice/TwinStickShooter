// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "EnemyCharacter.h"
#include "TwinStickGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DataTable.h"
#include "SpawnerTable.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BoxComponent) == false) {
		UE_LOG(LogTemp, Warning, TEXT("ASpawner::BeginPlay IsValid(BoxComponent) == false"))
	}
	
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Warning, TEXT("ASpawner::BeginPlay IsValid(World) == false"))
		return;
	}

}

void ASpawner::SpawnEnemy(TSubclassOf<AEnemyCharacter> EnemyTemplate) {
	if (IsValid(BoxComponent) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::SpawnEnemy IsValid(BoxComponent) == false"))
			return;
	}
	if (IsValid(EnemyTemplate) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::SpawnEnemy IsValid(EnemyTemplate) == false"))
			return;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("ASpawner::SpawnEnemy IsValid(World) == false"))
			return;
	}

	//Spawn enemy at random location inside bounding box
	FVector ActorLocation = GetActorLocation();
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
	FTransform EnemySpawnPosition = FTransform(
		UKismetMathLibrary::RandomPointInBoundingBox(
			ActorLocation,
			BoxExtent
		)
	);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AEnemyCharacter* Enemy = World->SpawnActor<AEnemyCharacter>(EnemyTemplate.Get(), EnemySpawnPosition, SpawnParameters);
	
	if (IsValid(Enemy) == false) {
		UE_LOG(LogTemp, Warning, TEXT("ASpawner::SpawnEnemies (Enemy) == false"))
		return;
	}
	
	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(World->GetAuthGameMode());
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("ASpawner::BeginPlay IsValid(GameMode) == false"));
		return;
	}
	GameMode->IncrementEnemyCounter(1);
}


