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

	SpawnEnemyWaveOnNextFrame();
	/*
	ConstructorHelpers::FObjectFinder<UDataTable>
		SpawnerLookupTable_BP(TEXT("DataTable'/Game/TwinSticksShooter/DataTables/SpawnerTable.SpawnerTable'"));
	//TODO: check if object loading succeeded
	SpawnerLookupTable = SpawnerLookupTable_BP.Object;
	if (IsValid(SpawnerLookupTable) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay IsValid(SpawnerLookupTable) == false"))
	}
	*/
	
}


void ANexusDefenceGameMode::SpawnEnemyWaveOnNextFrame() {
	GetWorldTimerManager().SetTimerForNextTick(
		this,
		&ANexusDefenceGameMode::SpawnEnemyWave
	);
}

void ANexusDefenceGameMode::SpawnEnemyWave() {
	
	
	/*
	if (IsValid(SpawnerLookupTable) == false) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay IsValid(SpawnerLookupTable) == false"))
		return;
	}

	FString ContextString(TEXT("GENERAL"));
	FName WaveName = FName(*FString::FromInt(CurrentWaveIndex));
	FSpawnerTable* SpawnerLookupRow = SpawnerLookupTable->FindRow(WaveName, ContextString);
	if (SpawnerLookupRow == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("ANexusDefenceGameMode::BeginPlay SpawnerLookupRow == nullptr"))
		return;
	}
	else { // we have the spawner lookup row data
		UE_LOG(LogTemp, Display, TEXT("SpawnerLookupRow data found"))
	}

	TAssetPtr<AEnemyCharacter> EnemyAssetPtr = SpawnerLookupRow->EnemyAsset;
	FStreamableManager AssetLoader;
	FStringAssetReference AssetToLoad;
	AssetToLoad = EnemyAssetPtr.ToStringReference();
	AssetLoader.SimpleAsyncLoad(AssetToLoad);


	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawner::StaticClass(), Spawners);
	for (int i = 0; i < SpawnerLookupRow->EnemyCount; i++) {
		ASpawner* Spawner = Cast<ASpawner>(Spawners[i % Spawners.Num()]);
		Spawner->SpawnEnemy(EnemyAssetPtr.Get());
	}

	*/
	if (validate(CurrentWaveIndex <= EnemiesPerWave.Num()) == false) { return; }

	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawner::StaticClass(), Spawners);
	if (CurrentWaveIndex == EnemiesPerWave.Num()) { // Boss Wave
		UE_LOG(LogTemp, Display, TEXT("Spawning Boss"))
		ASpawner* Spawner = Cast<ASpawner>(Spawners[0]);
		Spawner->SpawnEnemy(BossTemplate);
	}
	else { //Regular Wave
		int EnemiesThisWave = EnemiesPerWave[CurrentWaveIndex];
		for (int i = 0; i < EnemiesThisWave; i++) {
			ASpawner* Spawner = Cast<ASpawner>(Spawners[i % Spawners.Num()]);
			Spawner->SpawnEnemy(EnemyClass);
		}
	}
}

void ANexusDefenceGameMode::RespawnPlayer()
{
	Super::RespawnPlayer();
	CurrentWaveIndex = 0;
	SpawnEnemyWaveOnNextFrame();

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
		if (validate(IsValid(NexusStatsWidget)) == false) { return; }

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
		if (CurrentWaveIndex > EnemiesPerWave.Num()) { //We win the game after all the enemy waves and the boss wave
			WinGame();
		}
		//TODO: add delay
		SpawnEnemyWaveOnNextFrame();
	}
}
