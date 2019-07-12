// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"
#include "Projectile.h"
#include "CustomMacros.h"

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
	if (validate(IsValid(World)) == false) { return; }

	World->GetTimerManager().SetTimer(
		FireTimerHandle,
		this,
		&AGun::Fire,
		1 / GetFireRate(),
		true,
		0.0f
	);
}


void AGun::ReleaseTrigger() {
	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	World->GetTimerManager().ClearTimer(FireTimerHandle);
}


void AGun::Fire() {
	PlayFireSound();
	SpawnProjectile();
}


void AGun::SpawnProjectile() {
	if (validate(IsValid(GunSpawnPosition)) == false) { return; }

	if (validate(IsValid(ProjectileTemplate)) == false) { return; }

	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	APawn* Player = World->GetFirstPlayerController()->GetPawn();
	if (validate(IsValid(Player)) == false) { return; }

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.Owner = Player;
	SpawnParameters.Instigator = Player->Instigator;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector GunSpawnLocation = GunSpawnPosition->GetComponentLocation();
	FRotator GunSpawnRotation = FRotator(0, GunSpawnPosition->GetComponentRotation().Yaw, 0);
	
	AProjectile* Projectile = World->SpawnActor<AProjectile>(
		ProjectileTemplate.Get(),
		GunSpawnLocation,
		GunSpawnRotation,
		SpawnParameters
	);

	validate(IsValid(Projectile));
}


void AGun::PlayFireSound() {
	if (validate(IsValid(FireSoundComponent)) == false) { return; }

	FireSoundComponent->Play();
}

float AGun::GetFireRate() {
	return FireRate;
}