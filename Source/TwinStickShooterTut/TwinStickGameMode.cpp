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
#include "CharacterPlayerController.h"
#include "CustomMacros.h"

void ATwinStickGameMode::BeginPlay()
{
	Super::BeginPlay();
	validate(IsValid(PlayerTemplate));

	FindPlayerControllers();
}

void ATwinStickGameMode::FindPlayerControllers() {
	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	PlayerControllers.Reset();
	TArray<AActor*> PlayerControllerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterPlayerController::StaticClass(), PlayerControllerActors);

	for (AActor* PlayerControllerActor : PlayerControllerActors) {
		ACharacterPlayerController* PlayerController = Cast<ACharacterPlayerController>(PlayerControllerActor);
		if (validate(IsValid(PlayerController))) {
			PlayerControllers.Add(PlayerController);
		}
	}
}

void ATwinStickGameMode::IncrementScore(const int Amount)
{
	CurrentScore += Amount;
	UpdateHUDScore(CurrentScore);
}

void ATwinStickGameMode::UpdateHUDScore(int Score) {
	for (ACharacterPlayerController* PlayerController : PlayerControllers) {
		if (validate(IsValid(PlayerController)) == false) { continue; }

		ATwinSticksHUD* TwinSticksHUD = Cast<ATwinSticksHUD>(PlayerController->GetHUD());
		if (validate(IsValid(TwinSticksHUD)) == false) { continue; }

		UPlayerStatsWidget* PlayerStats = TwinSticksHUD->GetPlayerStatsWidget();
		if (validate(IsValid(PlayerStats))) {
			PlayerStats->SetScore(Score);
		}
	}
}


// FIXME: PLS na otdelni funkcii
void ATwinStickGameMode::RespawnPlayer()
{
	UWorld* World = GetWorld();
	if (validate(IsValid(World) == false)) { return; }

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (validate(IsValid(FirstPlayerController)) == false) { return; }

	APawn* PlayerCharacter = FirstPlayerController->GetPawn();
	if (IsValid(PlayerCharacter)) {
		PlayerCharacter->Destroy();
	}

	
	// Destroy all enemies before respawning the player
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(World, EnemyClass, EnemyActors);
	for (auto&& Enemy : EnemyActors) {
		Enemy->Destroy();
	}
	
	if (validate(IsValid(PlayerTemplate)) == false) { return; }
	//Spawn The player and possess him by the player controller
	ATwinSticksCharacter* PlayerActor = World->SpawnActor<ATwinSticksCharacter>(PlayerTemplate, PlayerRespawnLocation);
	FirstPlayerController->Possess(PlayerActor);

	CurrentEnemies = 0;
}

void ATwinStickGameMode::WinGame()
{

}

void ATwinStickGameMode::LoseGame()
{

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
}

void ATwinStickGameMode::SetPlayerRespawnLocation(FTransform Location)
{
	PlayerRespawnLocation = Location;
}

void ATwinStickGameMode::RestartLevel() {
	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	UGameplayStatics::OpenLevel(this, FName(*World->GetName()), false);
}


void ATwinStickGameMode::LoadWinLevel() {
	UGameplayStatics::OpenLevel(this, WinGameLevel, false);
}