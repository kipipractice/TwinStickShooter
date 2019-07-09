// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "EnemyCharacter.h"
#include "TwinStickGameMode.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

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
	Cast<ATwinStickGameMode>(World->GetAuthGameMode())->OnSpawnEnemies.AddDynamic(this, &ASpawner::SpawnEnemy);

	
}


void ASpawner::SpawnEnemy() {
	if (IsValid(BoxComponent) == false) {
		UE_LOG(LogTemp, Error, TEXT("ASpawner::SpawnEnemy IsValid(BoxComponent) == false"))
		return;
	}
	if(EnemyClasses.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("ASpawner::SpawnEnemy EnemyClasses.Num() == 0"))
		return;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("ASpawner::SpawnEnemy IsValid(World) == false"))
		return;
	}
	FVector ActorLocation = GetActorLocation();
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();

	for (auto&& EnemyClass : EnemyClasses) {
		FTransform EnemySpawnPosition = FTransform(
			UKismetMathLibrary::RandomPointInBoundingBox(
				ActorLocation,
				BoxExtent
			)
		);
		World->SpawnActor<AEnemyCharacter>(EnemyClass, EnemySpawnPosition);
	}
}

