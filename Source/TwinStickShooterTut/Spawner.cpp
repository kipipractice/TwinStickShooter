// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "TwinSticksCharacter.h"
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

void ASpawner::SpawnEnemy(TSubclassOf<ATwinSticksCharacter> EnemyTemplate, int Count) {
	if (validate(IsValid(BoxComponent))  == false) { return; }
	if (validate(IsValid(EnemyTemplate)) == false) { return; }

	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }


	for (int i = 0; i < Count; i++) {
		//Get random point inside the bounding box
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

		ATwinSticksCharacter* Enemy = World->SpawnActor<ATwinSticksCharacter>(
			EnemyTemplate,
			EnemySpawnPosition,
			SpawnParameters);
		if (validate(IsValid(Enemy)) == false) { continue;; }

		ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(World->GetAuthGameMode());
		if (validate(IsValid(GameMode)) == false) { continue;; }

		GameMode->IncrementEnemyCounter(1);
	
	}
	
}


