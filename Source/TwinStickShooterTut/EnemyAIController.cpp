// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "DebugPrinter.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "PlayerCharacter.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	
	ActorToFollow = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ActorToFollow) {
		DebugPrinter::Print("Actor to follow not found");
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


