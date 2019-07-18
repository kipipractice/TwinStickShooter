// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusDefenceGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "HealthComponent.h"
#include "CharacterPlayerController.h"
#include "NexusDefenceHUD.h"
#include "Nexus.h"
#include "NexusDefenceStatsWidget.h"
#include "TimerManager.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "SpawnerTable.h"
#include "Spawner.h"
#include "UnrealString.h"
#include "Engine/StreamableManager.h"
#include "UObject/SoftObjectPath.h"
#include "UObject/SoftObjectPtr.h"
#include "CustomMacros.h"
#include "TwinSticksCharacter.h"

void ANexusDefenceGameMode::BeginPlay() {
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	TArray<AActor*> NexusArray;
	UGameplayStatics::GetAllActorsOfClass(World, ANexus::StaticClass(), NexusArray);
	if (validate(NexusArray.Num() == 1) == false) { return; }

	ANexus* Nexus = Cast<ANexus>(NexusArray[0]);
	if (validate(IsValid(Nexus)) == false) { return; }
	
	UHealthComponent* HealthComponent = Nexus->FindComponentByClass<UHealthComponent>();
	if (validate(IsValid(HealthComponent)) == false) { return; }

	HealthComponent->OnDeath.AddDynamic(this, &ANexusDefenceGameMode::LoseGame);
	HealthComponent->OnHealthChanged.AddDynamic(this, &ANexusDefenceGameMode::SetNexusHealth);

	this->Nexus = Nexus;

	if (validate(IsValid(SpawnerLookupTable))) { 
		WaveCount = SpawnerLookupTable->GetRowNames().Num();
		UE_LOG(LogTemp, Display, TEXT("%d"), WaveCount);
		SpawnEnemyWave();
	}
}



void ANexusDefenceGameMode::SpawnEnemyWave() {
	if (CurrentWaveIndex == WaveCount) {
		UE_LOG(LogTemp, Display, TEXT("Finished all the waves"))
		WinGame();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawn wave %d"), CurrentWaveIndex);

	if (validate(IsValid(SpawnerLookupTable)) == false) { return; }

	FString ContextString(TEXT("GENERAL"));
	FName WaveName = FName(*FString::FromInt(CurrentWaveIndex));
	FSpawnerTable* SpawnerLookupRow = SpawnerLookupTable->FindRow<FSpawnerTable>(WaveName, ContextString);
	if (validate(SpawnerLookupRow != nullptr) == false) { return; }
	TArray<FSpawnerInfo> WaveInfo = SpawnerLookupRow->SpawnerEnemyPlacement;
	
	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawner::StaticClass(), Spawners);
	
	if (validate(WaveInfo.Num() >= Spawners.Num()) == false) { return; }

	for (int i = 0; i < Spawners.Num(); i++) {
		ASpawner* Spawner = Cast<ASpawner>(Spawners[i]);
		FSpawnerInfo SpawnInfo = WaveInfo[i];
		if (validate(IsValid(Spawner)) == false) { continue; }
		if (validate(IsValid(SpawnInfo.EnemyAsset)) == false) { continue; }
		Spawner->SpawnEnemy(SpawnInfo.EnemyAsset, SpawnInfo.EnemyCount);
	}
}

void ANexusDefenceGameMode::RespawnPlayer()
{
	Super::RespawnPlayer();

	if (validate(IsValid(Nexus))) {
		UHealthComponent* HealthComponent = Nexus->FindComponentByClass<UHealthComponent>();
		if (validate(IsValid(HealthComponent))) {
			HealthComponent->TakeDamage(DamageToNexusPerRespawn);
		}
	}

	/*
	UNexusDefenceStatsWidget* NexusStatsWidget = GetNexusStatsWidget();
	if (validate(IsValid(NexusStatsWidget))) {
		UHealthComponent* HealthComponent = Nexus->FindComponentByClass<UHealthComponent>();
		if (validate(IsValid(HealthComponent))) {
			NexusStatsWidget->SetNexusHealth(HealthComponent->GetHealth());
		}
	}
	*/

	// CurrentWaveIndex = 0;
	SpawnEnemyWave();
}

UNexusDefenceStatsWidget* ANexusDefenceGameMode::GetNexusStatsWidget(APlayerController* PlayerController)
{
	if (validate(IsValid(PlayerController)) == false) { return nullptr; }

	ANexusDefenceHUD* NexusDefenceHUD = Cast<ANexusDefenceHUD>(PlayerController->GetHUD());
	if (validate(IsValid(NexusDefenceHUD)) == false) { return nullptr; }

	return NexusDefenceHUD->GetNexusDefenceWidget();
}

void ANexusDefenceGameMode::SetNexusHealth(int Health) {
	for (ACharacterPlayerController* PlayerController : PlayerControllers) {
		if (validate(IsValid(PlayerController)) == false) { return; }

		ANexusDefenceHUD* NexusDefenceHUD = Cast<ANexusDefenceHUD>(PlayerController->GetHUD());
		if (validate(IsValid(NexusDefenceHUD)) == false) { return; }

		UNexusDefenceStatsWidget* NexusStatsWidget = NexusDefenceHUD->GetNexusDefenceWidget();
		if (validate(NexusStatsWidget)) {
			NexusStatsWidget->SetNexusHealth(Health);
		}
	}
}


ANexus* ANexusDefenceGameMode::GetNexus() {
	if (validate(IsValid(Nexus)) == false) { return nullptr; };

	return Nexus;
}


void ANexusDefenceGameMode::LoseGame() {
	Super::LoseGame();
	for (ACharacterPlayerController* PlayerController : PlayerControllers) {
		UNexusDefenceStatsWidget* NexusStatsWidget = GetNexusStatsWidget(PlayerController);
		if (validate(IsValid(NexusStatsWidget))) {
			NexusStatsWidget->SetLoseGame();
		}
		
		FTimerHandle RespawnTimerHandle; // not used anywhere
		GetWorldTimerManager().SetTimer(
			RespawnTimerHandle,
			this,
			&ATwinStickGameMode::RestartLevel,
			3
		);
	}
}

void ANexusDefenceGameMode::WinGame() {
	Super::WinGame();
	for (ACharacterPlayerController* PlayerController : PlayerControllers) {

		UNexusDefenceStatsWidget * NexusStatsWidget = GetNexusStatsWidget(PlayerController);

		if (validate(IsValid(NexusStatsWidget))) {
			NexusStatsWidget->SetWinGame();
		}

		FTimerHandle RespawnTimerHandle; // not used anywhere
		GetWorldTimerManager().SetTimer(
			RespawnTimerHandle,
			this,
			&ATwinStickGameMode::LoadWinLevel,
			3
		);
	}
}

void ANexusDefenceGameMode::DecrementEnemyCounter()
{
	Super::DecrementEnemyCounter();
	if (AreAllEnemiesDead()) {
		CurrentWaveIndex++;
		if (CurrentWaveIndex == WaveCount) { //We win the game after all the enemy waves and the boss wave
			UE_LOG(LogTemp, Display, TEXT("You won the game"));
			WinGame();
		}
		//TODO: add delay
		SpawnEnemyWave();
	}
}
