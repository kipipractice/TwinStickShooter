// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"
#include "Projectile.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FireSoundComponent = CreateDefaultSubobject<UAudioComponent>("FireAudioComponent");
	FireSoundComponent->bAutoActivate = false;
	FireSoundComponent->AttachTo(GetRootComponent());
}

void AGun::PullTrigger() {
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGun::ReleaseTrigger() IsValid(World) == false"));
		return;
	}
	// Call Fire because Timer function is called after the delay.
	Fire();

	World->GetTimerManager().SetTimer(
		FireTimerHandle,
		this,
		&AGun::Fire,
		1 / GetFireRate(),
		true
	);
}


void AGun::ReleaseTrigger() {
	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGun::ReleaseTrigger() IsValid(World) == false"));
		return;
	}
	World->GetTimerManager().ClearTimer(FireTimerHandle);
}


void AGun::Fire() {
	PlayFireSound();
	SpawnProjectile();
}


void AGun::SpawnProjectile() {
	if (IsValid(GunSpawnPosition) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGun::SpawnProjectile() IsValid(GunSpawnPosition) == false"));
		return;
	}

	if (IsValid(ProjectileTemplate) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGun::SpawnProjectile() IsValid(ProjectileTemplate) == false"));
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGun::SpawnProjectile() IsValid(World) == false"));
		return;
	}

	AActor* Player = World->GetFirstPlayerController()->GetPawn();
	if (IsValid(Player) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGun::SpawnProjectile() IsValid(Player) == false"));
	}

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.Owner = Player;
	SpawnParameters.Instigator = Player->Instigator;

	FVector GunSpawnLocation = GunSpawnPosition->GetComponentLocation();
	FRotator GunSpawnRotation = FRotator(0, GunSpawnPosition->GetComponentRotation().Yaw, 0);
	
	AProjectile* Projectile = World->SpawnActor<AProjectile>(
		ProjectileTemplate.Get(),
		GunSpawnLocation,
		GunSpawnRotation,
		SpawnParameters
	);
}


void AGun::PlayFireSound() {
	if (IsValid(FireSoundComponent) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGun::PlayFireSound() IsValid(FireSoundComponent) == false"));
		return;
	}

	FireSoundComponent->Play();
}

float AGun::GetFireRate() {
	return FireRate;
}