// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "EnemyCharacter.h"
#include "TwinStickGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DataTable.h"
#include "SpawnerTable.h"
#include "CustomMacros.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	validate(IsValid(BoxComponent));
}

void ASpawner::SpawnEnemy(TSubclassOf<AEnemyCharacter> EnemyTemplate) {
	if (validate(IsValid(BoxComponent))  == false) { return; }
	if (validate(IsValid(EnemyTemplate)) == false) { return; }

	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

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
	if (validate(IsValid(Enemy)) == false) { return; }
	
	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(World->GetAuthGameMode());
	if (validate(IsValid(GameMode)) == false) { return; }

	GameMode->IncrementEnemyCounter(1);
}


