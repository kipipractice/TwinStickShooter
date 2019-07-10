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
		&AEnemyAIController::ResetFollowTarget,
		TrackInterval,
		true,
		TrackDelay
	);
}
	

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DecideTarget();
	LookAtTarget();
}


void AEnemyAIController::DecideTarget() {
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (IsValid(PlayerCharacter) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(PlayerCharacter) == false"));
		return;
	}

	if (IsValid(ControlledEnemy) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(ControlledEnemy) == false"));
		return;
	}

	ANexus* Nexus = GetNexus();
	if (IsValid(Nexus) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(Nexus) == false"));
		return;
	}

	
	FVector EnemyLocation = ControlledEnemy->GetActorLocation();
	FVector NexusLocation = Nexus->GetActorLocation();
	float DistanceToNexus = FVector::Distance(EnemyLocation, NexusLocation);
	// Dont retarget if already in range of nexus. 
	// Otherwise player can cheese the enemies by switching targeting between nexus and player character.
	if (DistanceToNexus < TargetNexusDistance && CurrentlyTargetedActorType == EFollowActorType::Nexus) {
		return;
	}
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	float DistanceToPlayer = FVector::Distance(EnemyLocation, PlayerLocation);

	if (DistanceToPlayer < TargetPlayerDistance && CurrentlyTargetedActorType != EFollowActorType::Player) {
		SwitchTarget(EFollowActorType::Player);
	}
	else if (DistanceToPlayer >= TargetPlayerDistance && CurrentlyTargetedActorType != EFollowActorType::Nexus)
	{
		SwitchTarget(EFollowActorType::Nexus);
	}
}

void AEnemyAIController::LookAtTarget() {
	if (IsValid(TargetToFollow) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::LookAtTarget IsValid(TargetToFollow) == false"));
		return;
	}
	AActor* Pawn = GetPawn();
	if (IsValid(Pawn) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::LookAtTarget IsValid(Pawn) == false"));
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
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess IsValid(Pawn) == false"));
		return;
	}
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(PossessedPawn);
	if (IsValid(EnemyCharacter) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::OnPossess IsValid(EnemyCharacter) == false"));
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
			CurrentlyTargetedActorType = EFollowActorType::Player;
			break;
		case EFollowActorType::Nexus:
			NewTarget = GetNexus();
			CurrentlyTargetedActorType = EFollowActorType::Nexus;
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

void AEnemyAIController::ResetFollowTarget()
{
	if (IsValid(TargetToFollow) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::FollowActor IsValid(TargetToFollow) == false"))
		return;
	}
	MoveToActor(TargetToFollow);
}