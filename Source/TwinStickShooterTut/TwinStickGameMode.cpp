// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerVolume.h"
#include "TwinSticksCharacter.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "TwinSticksHUD.h"
#include "PlayerStatsWidget.h"
#include "Spawner.h"


void ATwinStickGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(PlayerTemplate) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::BeginPlay IsValid(PlayerTemplate) == false"));
	}

	// Spawn enemies on next frame so that all the logic is initialized before that
	SpawnEnemyWaveOnNextFrame();
}


void ATwinStickGameMode::SpawnEnemyWave() {
	OnSpawnEnemies.Broadcast(CurrentWaveIndex);
}


void ATwinStickGameMode::SpawnEnemyWaveOnNextFrame() {
	GetWorldTimerManager().SetTimerForNextTick(
		this, 
		&ATwinStickGameMode::SpawnEnemyWave
	);
}


void ATwinStickGameMode::IncrementScore(const int Amount)
{
	CurrentScore += Amount;
	UpdateHUDScore(CurrentScore);
}


void ATwinStickGameMode::UpdateHUDScore(int Score) {
	TArray<AActor*> HUDs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), HUDClass, HUDs);
	for (AActor* HUD : HUDs) {
		ATwinSticksHUD* TwinSticksHUD = Cast<ATwinSticksHUD>(HUD);
		if (IsValid(TwinSticksHUD) == false) {
			UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::UpdateHUDScore IsValid(TwinSticksHUD) == false"));
			continue;
		}
		UPlayerStatsWidget* PlayerStats = TwinSticksHUD->GetPlayerStatsWidget();
		if (IsValid(PlayerStats)) {
			PlayerStats->SetScore(Score);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::UpdateHUDScore IsValid(PlayerStats) == false"));
			continue;
		}
	}
}


// TODO: Split into separate functions
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
	
	if (IsValid(PlayerTemplate) == false) {
		UE_LOG(LogTemp, Error, TEXT("ATwinStickGameMode::RespawnPlayer IsValid(PlayerTemplate) == false"));
		return;
	}
	//Spawn The player and possess him by the player controller
	ATwinSticksCharacter* PlayerActor = World->SpawnActor<ATwinSticksCharacter>(PlayerTemplate, PlayerRespawnLocation);
	FirstPlayerController->Possess(PlayerActor);

	// Reset spawners
	CurrentWaveIndex = 0;
	CurrentEnemies = 0;
	SpawnEnemyWaveOnNextFrame();
}

bool ATwinStickGameMode::AreAllEnemiesDead()
{
	return CurrentEnemies <= 0;
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
	PlayerRespawnLocation = Location;
}
