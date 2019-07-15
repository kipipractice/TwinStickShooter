// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyAIController.h"
#include "TimerManager.h"

void AMeleeEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(
		TrackPlayerTimerHandle,
		this,
		&AMeleeEnemyAIController::FollowTarget,
		TrackInterval,
		true,
		TrackDelay
	);
}
