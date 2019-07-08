// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "DebugPrinter.h"
#include "Engine/EngineTypes.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	ActorToFollow = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ActorToFollow) {
		DebugPrinter::Print("Actor to follow not found");
		return;
	}
	GetWorldTimerManager().SetTimer(
		TrackPlayerTimerHandle,
		this,
		&AEnemyAIController::FollowActor,
		TrackInterval,
		true,
		TrackDelay);
}
	

void AEnemyAIController::Tick(float DeltaTime)
{
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(
		GetPawn()->GetActorLocation(),
		ActorToFollow->GetActorLocation()
	);
	GetPawn()->SetActorRotation(NewRotation);
}

void AEnemyAIController::FollowActor()
{
	if (!ensure(ActorToFollow)) {
		return;
	}
	MoveToActor(ActorToFollow);
}