// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "TwinSticksCharacter.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawner::Tick(float DeltaTime) {

}


void ASpawner::SpawnEnemy() {
	/*
	FVector Position = FVector(0, 0, 100);
	GetWorld()->SpawnActor<ATwinSticksCharacter>(
		CharacterTemplate,
		Position,
		FRotator(0, 0, 0)
	);
	*/
}