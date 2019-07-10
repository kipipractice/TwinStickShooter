// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "EnemyCharacter.h"
#include "TwinStickGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	Cast<ATwinStickGameMode>(World->GetAuthGameMode())->OnSpawnEnemies.AddDynamic(this, &ASpawner::SpawnEnemyWave);
	
}

void ASpawner::SpawnEnemyWave(int WaveIndex)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Warning, TEXT("ASpawner::BeginPlay IsValid(World) == false"))
			return;
	}
	if (WaveIndex > EnemiesPerWave.Num()) { // two more than the array
		return;
	}
	else if (WaveIndex == EnemiesPerWave.Num()) { // Boss battle after we finish spawning the specified number of enemies
		SpawnEnemy(BossTemplate);
		Cast<ATwinStickGameMode>(World->GetAuthGameMode())
			->IncrementEnemyCounter(1);
	}
	else {
		for (int i = 0; i < EnemiesPerWave[WaveIndex]; i++) {
			SpawnEnemy(EnemyTemplate);
		}
		Cast<ATwinStickGameMode>(World->GetAuthGameMode())
			->IncrementEnemyCounter(EnemiesPerWave[WaveIndex]);
	}
	
	
}

void ASpawner::SpawnEnemy(TSubclassOf<AEnemyCharacter> EnemyTemplate) {
	if (IsValid(BoxComponent) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::SpawnEnemy IsValid(BoxComponent) == false"))
			return;
	}
	if (IsValid(EnemyTemplate) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::SpawnEnemy EnemyClasses.Num() == 0"))
			return;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("ASpawner::SpawnEnemy IsValid(World) == false"))
			return;
	}
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
	World->SpawnActor<AEnemyCharacter>(EnemyTemplate, EnemySpawnPosition, SpawnParameters);
}


