// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	/*
	ActorToFollow = GetWorld()->GetFirstPlayerController()->GetPawn();
	MoveToActor(ActorToFollow);
	*/
}


void AEnemyAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

