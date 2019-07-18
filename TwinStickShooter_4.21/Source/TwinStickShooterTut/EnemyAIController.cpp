// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "NexusDefenceGameMode.h"
#include "Nexus.h"
#include "CustomMacros.h"


AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();

}
	

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DecideTarget();
	LookAtTarget();
}


void AEnemyAIController::DecideTarget() {
	//We cannot change target if we are already locked to the nexus
	if (bLockedToNexus) return;

	if (validate(IsValid(ControlledEnemy)) == false) { return; }

	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (validate(IsValid(PlayerCharacter)) == false) { return; }

	ANexus* Nexus = GetNexus();
	if (validate(IsValid(Nexus)) == false) { return; }
	
	FVector EnemyLocation = ControlledEnemy->GetActorLocation();
	FVector NexusLocation = Nexus->GetActorLocation();
	float DistanceToNexus = FVector::Distance(EnemyLocation, NexusLocation);
	// Dont retarget if already in range of nexus. 
	// Otherwise player can cheese the enemies by switching targeting between nexus and player character.
	if (DistanceToNexus < TargetNexusDistance && CurrentlyTargetedActorType == EFollowActorType::Nexus) {
		bLockedToNexus = true;
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
	if (validate(IsValid(Target)) == false) { return; }

	AActor* Pawn = GetPawn();
	if (validate(IsValid(Pawn)) == false) { return; }

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(
		Pawn->GetActorLocation(),
		Target->GetActorLocation()
	);
	FRotator PawnRotation = Pawn->GetActorRotation();
	PawnRotation.Yaw = NewRotation.Yaw;
	Pawn->SetActorRotation(PawnRotation);
}

/*
void AEnemyAIController::OnPossess(APawn* PossessedPawn) {
	Super::OnPossess(PossessedPawn);

	if (validate(IsValid(PossessedPawn)) == false) { return; }

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(PossessedPawn);
	if (validate(IsValid(EnemyCharacter)) == false) { return; }

	ControlledEnemy = EnemyCharacter;

	SwitchTarget(DefaultActorTypeToFollow);
}


*/
void AEnemyAIController::SwitchTarget(EFollowActorType ActorTypeToFollow) {
	if (validate(IsValid(ControlledEnemy)) == false) { return; }

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
			validate(false);
			return;
	}

	if (validate(IsValid(NewTarget)) == false) { return; }

	Target = NewTarget;
	ControlledEnemy->SetTarget(Target);
}

APlayerCharacter* AEnemyAIController::GetPlayerCharacter() {
	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return nullptr; }

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (validate(IsValid(FirstPlayerController)) == false) { return nullptr; }

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(FirstPlayerController->GetPawn());
	if (validate(IsValid(PlayerCharacter)) == false) { return nullptr; }

	return PlayerCharacter;
}

ANexus* AEnemyAIController::GetNexus() {
	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return nullptr; }

	ANexusDefenceGameMode* NexusDefenceMode = Cast<ANexusDefenceGameMode>(World->GetAuthGameMode());
	if (validate(IsValid(NexusDefenceMode)) == false) { return nullptr; }

	ANexus* Nexus = NexusDefenceMode->GetNexus();
	if (validate(IsValid(Nexus)) == false) { return nullptr; }

	return Nexus;
}

void AEnemyAIController::FollowTarget()
{
	if (validate(IsValid(Target)) == false) { return; }

	MoveToActor(Target);
}