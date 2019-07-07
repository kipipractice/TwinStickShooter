// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickGameMode.h"
#include "DebugPrinter.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TwinSticksCharacter.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "TwinSticksHUD.h"

void ATwinStickGameMode::BeginPlay()
{
	Super::BeginPlay();
	//DebugPrinter::Print("Some message");
	//GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandler, &ATwinStickGameMode::SpawnEnemies, WaveTimeInterval, true, 0.0f);
	GetWorldTimerManager().SetTimer(SpawnTimerHandler, this, &ATwinStickGameMode::SpawnEnemies, WaveTimeInterval, true, 0.0f);
}

void ATwinStickGameMode::IncrementScore(const int Amount)
{
	this->CurrentScore += Amount;

	UpdateHUDScore(this->CurrentScore);
}


void ATwinStickGameMode::UpdateHUDScore(int Score) {
	TArray<AActor*> HUDs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), HUDClass, HUDs);
	for (AActor* HUD : HUDs) {
		ATwinSticksHUD* TwinSticksHUD = Cast<ATwinSticksHUD>(HUD);
		if (TwinSticksHUD) {
			TwinSticksHUD->SetScore(Score);
		}
	}
}

void ATwinStickGameMode::RespawnPlayer()
{
	//DebugPrinter::Print("Spawning enemy");
	//Destroy all enemy actors
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, EnemyActors);
	for (auto&& Enemy : EnemyActors) {
		Enemy->Destroy();
	}
	ATwinSticksCharacter* PlayerActor = GetWorld()->SpawnActor<ATwinSticksCharacter>(PlayerClass, PlayerRespawnLocation);
	//DebugPrinter::Print("Spawned player character");
	GetWorld()->GetFirstPlayerController()->Possess(PlayerActor);
}


void ATwinStickGameMode::SpawnEnemies()
{
	//DebugPrinter::Print("Spawning enemy");
	OnSpawnEnemies.Broadcast();

}


void ATwinStickGameMode::SetPlayerRespawnLocation(FTransform PlayerRespawnTransform) {
	PlayerRespawnLocation = PlayerRespawnTransform;
}