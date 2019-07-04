// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickGameMode.h"
#include "DebugPrinter.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TwinSticksCharacter.h"

void ATwinStickGameMode::BeginPlay()
{
	Super::BeginPlay();
	DebugPrinter::Print("Some message");

}

void ATwinStickGameMode::IncrementScore(const int Amount)
{
	this->CurrentScore += Amount;
}

void ATwinStickGameMode::RespawnPlayer()
{
	DebugPrinter::Print("Spawning enemy");
	//Destroy all enemy actors
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, EnemyActors);
	for (auto&& Enemy : EnemyActors) {
		Enemy->Destroy();
	}
	ATwinSticksCharacter* PlayerActor = GetWorld()->SpawnActor<ATwinSticksCharacter>(PlayerClass, PlayerRespawnLocation);
	DebugPrinter::Print("Spawned player character");
	GetWorld()->GetFirstPlayerController()->Possess(PlayerActor);
}

void ATwinStickGameMode::SetPlayerRespawnLocation(const FTransform& Location)
{

}
