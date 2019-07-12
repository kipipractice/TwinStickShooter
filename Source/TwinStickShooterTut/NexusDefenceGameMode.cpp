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
	HealthComponent->OnHealthChanged.AddDynamic(this, &ANexusDefenceGameMode::SetNexusHealth);

	this->Nexus = Nexus;

	if (IsValid(SpawnerLookupTable) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay IsValid(SpawnerLookupTable) == false"))
	}
	else {
		WaveCount = SpawnerLookupTable->GetRowNames().Num();
		UE_LOG(LogTemp, Display, TEXT("%d"), WaveCount)
	}
	SpawnEnemyWave();
}



void ANexusDefenceGameMode::SpawnEnemyWave() {
	

	if (CurrentWaveIndex == WaveCount) {
		UE_LOG(LogTemp, Display, TEXT("Finished all the waves"))
		WinGame();
	}
	if (IsValid(SpawnerLookupTable) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay IsValid(SpawnerLookupTable) == false"))
		return;
	}

	//TODO: Get the number of entries in the data table

	FString ContextString(TEXT("GENERAL"));
	FName WaveName = FName(*FString::FromInt(CurrentWaveIndex));
	FSpawnerTable* SpawnerLookupRow = SpawnerLookupTable->FindRow<FSpawnerTable>(WaveName, ContextString);
	if (SpawnerLookupRow == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay SpawnerLookupRow == nullptr"))
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("SpawnerLookupRow data found"))
	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawner::StaticClass(), Spawners);
	for (int i = 0; i < SpawnerLookupRow->EnemyCount; i++) {
		ASpawner* Spawner = Cast<ASpawner>(Spawners[i % Spawners.Num()]);
		Spawner->SpawnEnemy(SpawnerLookupRow->EnemyAsset);
	}
	
}

void ANexusDefenceGameMode::RespawnPlayer()
{
	Super::RespawnPlayer();
	CurrentWaveIndex = 0;
	SpawnEnemyWave();

}

UNexusDefenceStatsWidget* ANexusDefenceGameMode::GetNexusStatsWidget(APlayerController* PlayerController)
{
	if (IsValid(PlayerController) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::SetNexusHealth IsValid(PlayerController) == false"));
		return nullptr;
	}

	ANexusDefenceHUD* NexusDefenceHUD = Cast<ANexusDefenceHUD>(PlayerController->GetHUD());
	if (IsValid(NexusDefenceHUD) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::SetNexusHealth IsValid(NexusDefenceHUD) == false"));
		return nullptr;
	}
	return NexusDefenceHUD->GetNexusDefenceWidget();
}

void ANexusDefenceGameMode::SetNexusHealth(int Health) {
	for (ACharacterPlayerController* PlayerController : PlayerControllers) {
		if (IsValid(PlayerController) == false) {
			UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::SetNexusHealth IsValid(PlayerController) == false"));
			return;
		}

		ANexusDefenceHUD* NexusDefenceHUD = Cast<ANexusDefenceHUD>(PlayerController->GetHUD());
		if (IsValid(NexusDefenceHUD) == false) {
			UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::SetNexusHealth IsValid(NexusDefenceHUD) == false"));
			return;
		}

		UNexusDefenceStatsWidget* NexusStatsWidget = NexusDefenceHUD->GetNexusDefenceWidget();
		NexusStatsWidget->SetNexusHealth(Health);
	}
}


ANexus* ANexusDefenceGameMode::GetNexus() {
	return Nexus;
}


void ANexusDefenceGameMode::LoseGame() {
	Super::LoseGame();
	for (ACharacterPlayerController* PlayerController : PlayerControllers) {
		

		UNexusDefenceStatsWidget* NexusStatsWidget = GetNexusStatsWidget(PlayerController);
		if (IsValid(NexusStatsWidget)) {
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

		if (IsValid(NexusStatsWidget)) {
			NexusStatsWidget->SetWinGame();
		}
		/*

		FTimerHandle RespawnTimerHandle; // not used anywhere
		GetWorldTimerManager().SetTimer(
			RespawnTimerHandle,
			this,
			&ATwinStickGameMode::RestartLevel,
			3
		);
		*/
		UGameplayStatics::OpenLevel(this, WinGameLevel, false);
		
	}
}

void ANexusDefenceGameMode::DecrementEnemyCounter()
{
	Super::DecrementEnemyCounter();
	if (AreAllEnemiesDead()) {
		CurrentWaveIndex++;
		if (CurrentWaveIndex == WaveCount) { //We win the game after all the enemy waves and the boss wave
			UE_LOG(LogTemp, Display, TEXT("You won the game"))
			WinGame();
		}
		//TODO: add delay
		SpawnEnemyWave();
	}
}
