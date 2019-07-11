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
		NexusStatsWidget->SetLoseGame();
		
		FTimerHandle RespawnTimerHandle; // not used anywhere
		GetWorldTimerManager().SetTimer(
			RespawnTimerHandle,
			this,
			&ATwinStickGameMode::RestartLevel,
			3
		);
	}
}