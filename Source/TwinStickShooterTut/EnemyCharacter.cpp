// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "DebugPrinter.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "PlayerCharacter.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	if (!DamageBox) {
		DebugPrinter::Print("Enemy damage collision box not set");
	}
	else {
		DamageBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnBoxBeginOverlap);
		DamageBox->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapEnd);
	}
	PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerCharacter) {
		DebugPrinter::Print("Could not find target player");
	}

}


void AEnemyCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor) == PlayerCharacter) {
		DebugPrinter::Print("overlapping with player");
		GetWorldTimerManager().SetTimer(
			DamageTimerHandle,
			this,
			&AEnemyCharacter::DealDamage,
			DamageRate,
			true,
			DamageDelay);
	}

}

void AEnemyCharacter::DealDamage()
{

	if (!ensure(DamageBox)) {
		return;
	}
	PlayerCharacter->TakeDamage(DamagePerHit);
}

void AEnemyCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APlayerCharacter>(OtherActor) == PlayerCharacter) {
		GetWorldTimerManager().ClearTimer(DamageTimerHandle);
		DebugPrinter::Print("stop the damage timer");
	}
}


// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

