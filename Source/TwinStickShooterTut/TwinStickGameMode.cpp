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
	GetWorldTimerManager().SetTimer(SpawnTimerHandler, this, &ATwinStickGameMode::SpawnEnemies, WaveTimeInterval, true, 0.0f);
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
		if (TwinSticksHUD) {
			TwinSticksHUD->SetScore(Score);
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
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(World, EnemyClass, EnemyActors);
	// Destroy all enemies before respawning the player
	for (auto&& Enemy : EnemyActors) {
		Enemy->Destroy();
	}

	ATwinSticksCharacter* PlayerActor = World->SpawnActor<ATwinSticksCharacter>(PlayerClass, PlayerRespawnLocation);
	if (IsValid(PlayerActor)) {
		FirstPlayerController->Possess(PlayerActor);
	}
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