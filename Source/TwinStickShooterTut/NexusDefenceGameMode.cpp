// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusDefenceGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "HealthComponent.h"
#include "Nexus.h"


void ANexusDefenceGameMode::BeginPlay() {
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay IsValid(World) == false"));
		return;
	}

	TArray<AActor*> NexusArray;
	UGameplayStatics::GetAllActorsOfClass(World, ANexus::StaticClass(), NexusArray);
	if (NexusArray.Num() != 1) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay NexusArray.Num() != 0"));
		return;
	}

	ANexus* Nexus = Cast<ANexus>(NexusArray[0]);
	if (IsValid(Nexus) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay IsValid(Nexus) == false"));
		return;
	}
	
	UHealthComponent* HealthComponent = Nexus->FindComponentByClass<UHealthComponent>();
	if (IsValid(HealthComponent) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay IsValid(HealthComponent) == false"));
		return;
	}
	HealthComponent->OnDeath.AddDynamic(this, &ANexusDefenceGameMode::LoseGame);

	this->Nexus = Nexus;
}



ANexus* ANexusDefenceGameMode::GetNexus() {
	return Nexus;
}


void ANexusDefenceGameMode::LoseGame() {
	UE_LOG(LogTemp, Error, TEXT("Player has lost the game!"));
}