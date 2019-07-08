// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "EnemyCharacter.h"
#include "TwinStickGameMode.h"
#include "DebugPrinter.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	if (!BoxComponent) {
		DebugPrinter::Print("No box component attached to spawner", EMessageType::Error);
	}
	Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode())->OnSpawnEnemies.AddDynamic(this, &ASpawner::SpawnEnemy);

	
}


void ASpawner::SpawnEnemy() {
	if (!ensure(BoxComponent) && !ensure(EnemyClasses.Num() > 0)) {
		DebugPrinter::Print("No box component or enemy templates set");
		return;
	}
	//DebugPrinter::Print("Spawning Enemy");
	for (auto&& EnemyClass : EnemyClasses) {

		FTransform EnemySpawnPosition = FTransform(
			UKismetMathLibrary::RandomPointInBoundingBox(
				GetActorLocation(),
				BoxComponent->GetScaledBoxExtent()
			)
		);
		GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, EnemySpawnPosition);
	}


}

