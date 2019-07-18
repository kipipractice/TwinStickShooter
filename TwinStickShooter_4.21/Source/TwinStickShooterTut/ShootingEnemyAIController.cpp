// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingEnemyAIController.h"
#include "EnemyCharacter.h"
#include "CustomMacros.h"

void AShootingEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bFiring == false) {
		FollowTarget();
		if ((CurrentlyTargetedActorType == EFollowActorType::Player ||
			bLockedToNexus))
		{
			UE_LOG(LogTemp, Display, TEXT("AShootingEnemyAIController::Tick StartFiring()"));
			bFiring = true;
			ControlledEnemy->StartFiring();
		}
	}
	else if(CurrentlyTargetedActorType != EFollowActorType::Player && bLockedToNexus == false)
	{
		UE_LOG(LogTemp, Display, TEXT("AShootingEnemyAIController::Tick StopFiring()"));
		bFiring = false;
		ControlledEnemy->StopFiring();
	}
	
}


//FIXME: Calling the line trace function crashes the game
bool AShootingEnemyAIController::CanSeeTarget()
{
	UWorld* World;
	if (validate(IsValid(World)) == false) { return false; }
	if (validate(IsValid(ControlledEnemy)) == false) { return false; }
	if (validate(IsValid(Target)) == false) { return false; }
	
	
	FHitResult HitResult;
	if (World->LineTraceSingleByChannel(
		HitResult,
		ControlledEnemy->GetActorLocation(),
		Target->GetActorLocation(),
		ECollisionChannel::ECC_Pawn
	)) {
		AActor* HitActor = HitResult.GetActor();
		if (validate(IsValid(HitActor)) == false) { return false; }
		if (HitActor == Target) {
			return true;
		}
		return false;
	}
	return false;

}
