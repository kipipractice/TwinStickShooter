// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "NexusDefenceGameMode.h"
#include "Nexus.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		TrackPlayerTimerHandle,
		this,
		&AEnemyAIController::FollowActor,
		TrackInterval,
		true,
		TrackDelay
	);
}
	

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(TargetToFollow) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(TargetToFollow) == false"));
		return;
	}
	AActor* Pawn = GetPawn();
	if (IsValid(Pawn) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(Pawn) == false"));
		return;
	}

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(
		Pawn->GetActorLocation(),
		TargetToFollow->GetActorLocation()
	);
	FRotator PawnRotation = Pawn->GetActorRotation();
	PawnRotation.Yaw = NewRotation.Yaw;
	Pawn->SetActorRotation(PawnRotation);
}


void AEnemyAIController::OnPossess(APawn* PossessedPawn) {
	Super::OnPossess(PossessedPawn);
	
	if (IsValid(PossessedPawn) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::BeginPlay IsValid(Pawn) == false"));
		return;
	}
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(PossessedPawn);
	if (IsValid(EnemyCharacter) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::BeginPlay IsValid(EnemyCharacter) == false"));
		return;
	}
	ControlledEnemy = EnemyCharacter;

	SwitchTarget(DefaultActorTypeToFollow);
}

void AEnemyAIController::SwitchTarget(EFollowActorType ActorTypeToFollow) {
	if (IsValid(ControlledEnemy) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::SwitchTarget IsValid(ControlledPawn) == false"));
		return;
	}

	AActor* NewTarget = nullptr;
	switch (ActorTypeToFollow) {
		case EFollowActorType::Player:
			NewTarget = GetPlayerCharacter();
			break;
		case EFollowActorType::Nexus:
			NewTarget = GetNexus();
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::SwitchTarget Unsupported EFollowActorType!"));
			return;
	}

	if (IsValid(NewTarget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::SwitchTarget IsValid(NewTarget) == false"));
		return;
	}

	TargetToFollow = NewTarget;
	ControlledEnemy->SetTarget(TargetToFollow);
}

APlayerCharacter* AEnemyAIController::GetPlayerCharacter() {
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::GetPlayerCharacter IsValid(World) == false"));
		return nullptr;
	}
	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (IsValid(FirstPlayerController) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::GetPlayerCharacter IsValid(FirstPlayerController) == false) == false"));
		return nullptr;
	}

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(FirstPlayerController->GetPawn());
	if (IsValid(PlayerCharacter) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::GetPlayerCharacter IsValid(PlayerCharacter) == false"));
		return nullptr;
	}
	return PlayerCharacter;
}

ANexus* AEnemyAIController::GetNexus() {
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::GetNexus IsValid(World) == false"));
		return nullptr;
	}

	ANexusDefenceGameMode* NexusDefenceMode = Cast<ANexusDefenceGameMode>(World->GetAuthGameMode());
	if (IsValid(NexusDefenceMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::GetNexus IsValid(NexusDefenceMode) == false"));
		return nullptr;
	}

	ANexus* Nexus = NexusDefenceMode->GetNexus();
	if (IsValid(Nexus) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::GetNexus IsValid(NexusDefenceMode) == false"));
		return nullptr;
	}

	return Nexus;
}

void AEnemyAIController::FollowActor()
{
	if (IsValid(TargetToFollow) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::FollowActor IsValid(TargetToFollow) == false"))
		return;
	}
	MoveToActor(TargetToFollow);
}