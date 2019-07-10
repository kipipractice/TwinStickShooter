// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TwinSticksCharacter.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "TwinSticksHUD.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerVolume.h"
#include "Spawner.h"


void ATwinStickGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(PlayerTemplate) == false) {
		UE_LOG(LogTemp, Warning, TEXT("ATwinStickGameMode::BeginPlay IsValid(PlayerTemplate) == false"))
	}

	OnSpawnEnemies.Broadcast(CurrentWaveIndex);
	
}


void ATwinStickGameMode::IncrementScore(const int Amount)
{
	CurrentScore += Amount;
	UpdateHUDScore(CurrentScore);
}

bool ATwinStickGameMode::AreAllEnemiesDead()
{
	return CurrentEnemies == 0;
}


void ATwinStickGameMode::UpdateHUDScore(int Score) {
	TArray<AActor*> HUDs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), HUDClass, HUDs);
	for (AActor* HUD : HUDs) {
		ATwinSticksHUD* TwinSticksHUD = Cast<ATwinSticksHUD>(HUD);
		if (IsValid(TwinSticksHUD)) {
			TwinSticksHUD->SetScore(Score);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::UpdateHUDScore IsValid(TwinSticksHUD) == false"));
		}
	}
}

void ATwinStickGameMode::RespawnPlayer()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::RespawnPlayer IsValid(World) == false"))
		return;
	}
	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (IsValid(FirstPlayerController) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::RespawnPlayer IsValid(FirstPlayerController) == false"))
		return;
	}

	
	// Destroy all enemies before respawning the player
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(World, EnemyClass, EnemyActors);
	for (auto&& Enemy : EnemyActors) {
		Enemy->Destroy();
	}
	

	//Spawn The player and possess him by the player controller
	ATwinSticksCharacter* PlayerActor = World->SpawnActor<ATwinSticksCharacter>(PlayerTemplate, PlayerRespawnLocation);
	//if (IsValid(PlayerActor)) {
	//	FirstPlayerController->Possess(PlayerActor);
	//}
	World->GetFirstPlayerController()->Possess(PlayerActor);
}

void ATwinStickGameMode::IncrementEnemyCounter(int EnemyCount)
{
	CurrentEnemies += EnemyCount;
}

void ATwinStickGameMode::DecrementEnemyCounter()
{
	CurrentEnemies -= 1;
	if (AreAllEnemiesDead()) {
		//TODO: add delay
		CurrentWaveIndex++;
		OnSpawnEnemies.Broadcast(CurrentWaveIndex);
	}
}

void ATwinStickGameMode::SetPlayerRespawnLocation(FTransform Location)
{
	FTransform PlayerRespawnLocation = Location;
}
