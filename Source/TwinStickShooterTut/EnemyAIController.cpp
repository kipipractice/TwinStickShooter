// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/EngineTypes.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::BeginPlay IsValid(World) == false"))
		return;
	}
	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (IsValid(FirstPlayerController) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::BeginPlay IsValid(FirstPlayerController) == false) == false"))
		return;
	}
	ActorToFollow = Cast<APlayerCharacter>(FirstPlayerController->GetPawn());
	if (IsValid(ActorToFollow) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::BeginPlay IsValid(ActorToFollow) == false"))
		return;
	}
	GetWorldTimerManager().SetTimer(
		TrackActorTimerHandle,
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
	if (IsValid(ActorToFollow) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(ActorToFollow) == false"));
		return;
	}
	AActor* Pawn = GetPawn();
	if (IsValid(Pawn) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(Pawn) == false"));
		return;
	}
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(
		Pawn->GetActorLocation(),
		ActorToFollow->GetActorLocation()
	);
	Pawn->SetActorRotation(NewRotation);

	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(World) == false"));
		return;
	}
	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (IsValid(FirstPlayerController) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(FirstPlayerController) == false"));
		return;
	}

	AActor* PlayerPawn = FirstPlayerController->GetPawn();

	if (IsValid(PlayerPawn) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::Tick IsValid(PlayerPawn) == false"));
		return;
	}
	float Distance = FVector::Dist(
		FirstPlayerController->GetPawn()->GetActorLocation(),
		GetPawn()->GetActorLocation());

	if ((ActorToFollow == PlayerPawn)
		&& (Distance > FollowPlayerDistance)) {
		
		//ActorToFollow = Cast<>(World->GetAuthGameMode())
	}
	else if (Distance <= FollowPlayerDistance) {
		ActorToFollow = FirstPlayerController->GetPawn();
	}

}

void AEnemyAIController::FollowActor()
{
	if (IsValid(ActorToFollow) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEnemyAIController::FollowActor IsValid(ActorToFollow) == false"))
		return;
	}
	MoveToActor(ActorToFollow);
}